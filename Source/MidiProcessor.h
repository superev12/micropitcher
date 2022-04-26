#pragma once

#include <JuceHeader.h>
#include "PathHelper.h"

void setupMpe(juce::MidiBuffer& midiBuffer)
{
}

std::vector<double> sampleSemitoneDeviation(pathHelper::NodeArray nodeArray, float samplesPerMillisecond)
{
    double timeBetweenSamplesInMilliseconds = 1.0/samplesPerMillisecond;
    float pathTimeRangeInMilliseconds = nodeArray[nodeArray.size()-1].point.x - nodeArray[0].point.x;
    int numberOfSamplesInPath = std::floor(pathTimeRangeInMilliseconds / timeBetweenSamplesInMilliseconds);

    // get sample at timeBetweenSamplesInMilliseconds intervals
    std::vector<double> samples = {};
    for (int sampleIndex = 0; sampleIndex < numberOfSamplesInPath; sampleIndex++)
    {
        samples.push_back(10.0 * std::sin(sampleIndex/200.0f));
    }

    return samples;
}


juce::MidiMessageSequence renderNodeArrayToMidiSequence(pathHelper::NodeArray nodeArray)
{
    auto midiSequence = juce::MidiMessageSequence();

    // Add midiOn at path start
    juce::MidiMessage firstMessage = juce::MidiMessage::noteOn(1, 64, 0.5f);
    double firstMessageTime = (double) nodeArray[0].point.x;
    firstMessage.setTimeStamp(firstMessageTime);
    midiSequence.addEvent(firstMessage, firstMessageTime);
    juce::MidiMessage lastMessage = juce::MidiMessage::noteOff(1, 64, 1.0f);

    // Sample points in path middle
    float samplesPerMillisecond = 0.1f;
    std::vector<double> pitchDeviationSamples = sampleSemitoneDeviation(nodeArray, samplesPerMillisecond);
    std::vector<juce::MidiMessage> middleMessages = {};
    for (double pitchDeviationInSemitones : pitchDeviationSamples)
    {
        int pitchbend = juce::MidiMessage::pitchbendToPitchwheelPos((float) pitchDeviationInSemitones, 48.0f);
        juce::MidiMessage middleMessage = juce::MidiMessage::pitchWheel(1, pitchbend);
        middleMessages.push_back(middleMessage);
    }
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


