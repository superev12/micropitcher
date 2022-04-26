#pragma once

#include <JuceHeader.h>
#include <cmath>
#include <math.h>
#include "PathHelper.h"

void setupMpe(juce::MidiBuffer& midiBuffer)
{
}

/*
given the nodeArray of a path, and the number of samplesPerMillisecond to calculate,
returns a vector of the difference between the pitch location of the curve at that point, and the median pitch.
The output is expressed in semitones.
*/
std::vector<double> sampleSemitoneDeviation(pathHelper::NodeArray nodeArray, float samplesPerMillisecond)
{
    double timeBetweenSamplesInMilliseconds = 1.0/samplesPerMillisecond;
    float pathTimeRangeInMilliseconds = nodeArray[nodeArray.size()-1].point.x - nodeArray[0].point.x;
    int numberOfSamplesInPath = std::floor(pathTimeRangeInMilliseconds / timeBetweenSamplesInMilliseconds);

    std::vector<double> samples = {};
    for (int sampleIndex = 0; sampleIndex < numberOfSamplesInPath; sampleIndex++)
    {
        samples.push_back(10.0 * std::sin(sampleIndex/200.0f));
        samples.push_back(0.0);
    }
    return samples;
}


juce::MidiMessageSequence renderNodeArrayToMidiSequence(pathHelper::NodeArray nodeArray)
{
    auto midiSequence = juce::MidiMessageSequence();

    // Add noteOn at start
    juce::MidiMessage firstMessage = juce::MidiMessage::noteOn(1, 64, 0.5f);
    double firstMessageTime = (double) nodeArray[0].point.x;
    firstMessage.setTimeStamp(firstMessageTime);
    midiSequence.addEvent(firstMessage, firstMessageTime);

    // Add pitch modulations in middle
    /*
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
        //midiSequence.addEvent(middleMessage, middleMessageTime);
    }
    */

    // Add noteOff at end
    juce::MidiMessage lastMessage = juce::MidiMessage::noteOff(1, 64, 1.0f);
    double lastMessageTime = (double) nodeArray[nodeArray.size()-1].point.x;
    lastMessage.setTimeStamp(lastMessageTime);
    if (lastMessageTime == firstMessageTime) lastMessageTime += 5.0; // Special case to make sure single nodes get noteOff
    midiSequence.addEvent(lastMessage, lastMessageTime);

    if (midiSequence.getNumEvents() == 0)
    {
        DBG("this midi sequence had nothing in it");
    }

    return midiSequence;
}

/* 
Takes a series of Path Strings that define functional curves in the format 'l s 12 43 c 234 21 32 45 345 32'
and returns the midi sequence for an MPE compatible synth to play the curve where the curve represents pitch against time
*/
juce::MidiMessageSequence renderPathstringsToMidiSequence(std::vector<juce::String> pathStrings)
{
    if (pathStrings.size() == 0) return {};

    std::vector<pathHelper::NodeArray> pathsAsNodeArrays;
    for (auto pathString : pathStrings)
    {
        pathsAsNodeArrays.push_back(pathHelper::stringToNodeArray(pathString));
    }

    std::vector<juce::MidiMessageSequence> midiSequences = {};
    /*
    for (auto nodeArray : pathsAsNodeArrays)
    {
        midiSequences.push_back(renderNodeArrayToMidiSequence(nodeArray));
    }
    */

    juce::MidiMessageSequence outputMidiSequence;
    /*
    for (auto midiSequence : midiSequences)
    {
        outputMidiSequence.addSequence(midiSequence, 0.0);
    }
    */
    auto testMidiMessage = juce::MidiMessage::noteOff (1, 64, 1.0f);
    testMidiMessage.setTimeStamp(0.0);
    outputMidiSequence.addEvent(juce::MidiMessage::noteOff(1, 64, 1.0f));

    return outputMidiSequence;
}

