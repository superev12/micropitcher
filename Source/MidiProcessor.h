#pragma once

#include <JuceHeader.h>
#include <math.h>
#include "PathHelper.h"

void setupMpe(juce::MidiBuffer& midiBuffer)
{
}

double frequencyToMidiNote(double frequencyInHz)
{
    return 12.0*std::log2(frequencyInHz/440.0) + 69.0;
}

double midiNoteToFrequency(double midiNoteNumber)
{
    return 440 * std::pow(2, (midiNoteNumber-69)/12);
}

int getMedianMidiNoteNumber(pathHelper::NodeArray nodeArray)
{
    juce::Path path;
    path.restoreFromString(pathHelper::nodeArrayToString(nodeArray));

    juce::Rectangle<float> bounds = path.getBounds();

    // Note: The 'Bottom' of a shape in juce world is the part with the highest Y coordinate
    double topFrequency = bounds.getBottom();
    double bottomFrequency = bounds.getY();

    double topMidiNoteNumber = frequencyToMidiNote(topFrequency);
    double bottomMidiNoteNumber = frequencyToMidiNote(bottomFrequency);

    return (topMidiNoteNumber - bottomMidiNoteNumber) / 2.0;
}

double binarySearchPath(juce::Path& path, double target, double threshold, double start, double end)
{
    double middle = (start + end) / 2;

    juce::Point<float> pointAtMiddle = path.getPointAlongPath(middle);
    juce::Point<float> pointAtTarget = path.getPointAlongPath(target);
    
    // The current value is close enough
    if (std::abs(pointAtMiddle.x - pointAtTarget.x) < threshold) return pointAtMiddle.y;

    double nextStart, nextEnd;

    // The current value is too high
    if (pointAtMiddle.x > pointAtTarget.x)
    {
        nextStart = start;
        nextEnd = middle;
    }

    // The current value is too low
    if (pointAtMiddle.x <= pointAtTarget.x)
    {
        nextStart = middle;
        nextEnd = end;
    }

    return binarySearchPath(path, target, threshold, nextStart, nextEnd);
}

/*
find the difference from between the median pitch on a path and the current pitch, given a time in milliseconds
If the time given is outside the path, the time value is clamped to the time range of the path.
*/
double getSemitoneDeviationAtTime(pathHelper::NodeArray nodeArray, double timeInMilliseconds)
{
    // clamp timeInMilliseconds to the time bounds of the path
    float firstTimeOnCurve = nodeArray[0].point.x;
    float lastTimeOnCurve = nodeArray[nodeArray.size()-1].point.x;
    timeInMilliseconds = pathHelper::clampFloat(timeInMilliseconds, firstTimeOnCurve, lastTimeOnCurve);


    // Find the two nodes the time falls between
    juce::Path path;
    path.restoreFromString(pathHelper::nodeArrayToString(nodeArray));
    double frequencyAtSample = binarySearchPath(path, timeInMilliseconds, 1.0, firstTimeOnCurve, lastTimeOnCurve);

    int medianNoteMidiNumber = getMedianMidiNoteNumber(nodeArray);
    double midiNumberAtSample = frequencyToMidiNote(frequencyAtSample);

    return midiNumberAtSample - ((double) medianNoteMidiNumber);
}



std::vector<double> sampleSemitoneDeviation(pathHelper::NodeArray nodeArray, float samplesPerMillisecond)
{
    double timeBetweenSamplesInMilliseconds = 1.0/samplesPerMillisecond;
    float pathTimeRangeInMilliseconds = nodeArray[nodeArray.size()-1].point.x - nodeArray[0].point.x;
    int numberOfSamplesInPath = std::floor(pathTimeRangeInMilliseconds / timeBetweenSamplesInMilliseconds);

    // Get floored median note number
    int medianNoteMidiNumber = getMedianMidiNoteNumber(nodeArray);

    // get sample at timeBetweenSamplesInMilliseconds intervals
    std::vector<double> samples = {};
    for (int sampleIndex = 0; sampleIndex < numberOfSamplesInPath; sampleIndex++)
    {
        double deviation = getSemitoneDeviationAtTime(nodeArray, sampleIndex*timeBetweenSamplesInMilliseconds);
        samples.push_back(deviation);
    }

    return samples;
}


juce::MidiMessageSequence renderNodeArrayToMidiSequence(pathHelper::NodeArray nodeArray)
{
    auto midiSequence = juce::MidiMessageSequence();
    int medianMidiNoteNumber = getMedianMidiNoteNumber(nodeArray);

    // Add midiOn at path start
    juce::MidiMessage firstMessage = juce::MidiMessage::noteOn(1, medianMidiNoteNumber, 0.5f);
    double firstMessageTime = (double) nodeArray[0].point.x;
    firstMessage.setTimeStamp(firstMessageTime);
    midiSequence.addEvent(firstMessage, firstMessageTime);
    juce::MidiMessage lastMessage = juce::MidiMessage::noteOff(1, medianMidiNoteNumber, 1.0f);

    // Sample points in path middle
    float samplesPerMillisecond = 0.1f;
    std::vector<double> pitchDeviationSamples = sampleSemitoneDeviation(nodeArray, samplesPerMillisecond);

    // Middle points to midi messages
    std::vector<juce::MidiMessage> middleMessages = {};
    for (double pitchDeviationInSemitones : pitchDeviationSamples)
    {
        float clampedPitchDeviationInSemitones = pathHelper::clampFloat((float) pitchDeviationInSemitones, -48.0f, 48.0f);
        int pitchbend = juce::MidiMessage::pitchbendToPitchwheelPos(clampedPitchDeviationInSemitones, 48.0f);
        juce::MidiMessage middleMessage = juce::MidiMessage::pitchWheel(1, pitchbend);
        middleMessages.push_back(middleMessage);
    }
    // Add middle messages to sequence with timestamps
    for (int messageIndex = 0; messageIndex < middleMessages.size(); messageIndex++)
    {
        double timeBetweenSamplesInMilliseconds = 1.0/samplesPerMillisecond;
        double middleMessageTime = firstMessageTime + timeBetweenSamplesInMilliseconds * messageIndex;
        auto middleMessage = middleMessages[messageIndex];
        middleMessage.setTimeStamp(middleMessageTime);
        midiSequence.addEvent(middleMessage, middleMessageTime);
    }

    // Add midiOff at path end
    double lastMessageTime;
    if (nodeArray.size() == 1)
    {
        // Ensure single point paths have a nonzero duration
        lastMessageTime = (double) nodeArray[nodeArray.size()-1].point.x + 10;
    } else {
        lastMessageTime = (double) nodeArray[nodeArray.size()-1].point.x;
    }

    lastMessage.setTimeStamp(lastMessageTime);
    midiSequence.addEvent(lastMessage, lastMessageTime);

    return midiSequence;
}


juce::MidiMessageSequence renderPathstringsToMidiSequence(std::vector<juce::String> pathStrings)
{
    if (pathStrings.size() == 0) return {};

    // Turn pathstrings into nodeArrays
    std::vector<pathHelper::NodeArray> pathsAsNodeArrays;
    for (auto pathString : pathStrings)
    {
        pathsAsNodeArrays.push_back(pathHelper::stringToNodeArray(pathString));
    }

    // Render nodeArrays to MidiSequences
    std::vector<juce::MidiMessageSequence> midiSequences = {};
    for (auto nodeArray : pathsAsNodeArrays)
    {
        midiSequences.push_back(
            renderNodeArrayToMidiSequence(nodeArray)
        );
    }

    // Concatenate MidiSequences
    juce::MidiMessageSequence outputMidiSequence;
    for (auto midiSequence : midiSequences)
    {
        outputMidiSequence.addSequence(midiSequence, 0.0);
    }

    return outputMidiSequence;
}


