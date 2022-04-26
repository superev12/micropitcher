#pragma once

#include <JuceHeader.h>
#include "PathHelper.h"

void setupMpe(juce::MidiBuffer& midiBuffer)
{
}


juce::MidiMessageSequence renderNodeArrayToMidiSequence(pathHelper::NodeArray nodeArray)
{
    auto midiSequence = juce::MidiMessageSequence();

    juce::MidiMessage firstMessage = juce::MidiMessage::noteOn(1, 64, 0.5f);
    double firstMessageTime = (double) nodeArray[0].point.x;
    firstMessage.setTimeStamp(firstMessageTime);
    midiSequence.addEvent(firstMessage, firstMessageTime);

    juce::MidiMessage lastMessage = juce::MidiMessage::noteOff(1, 64, 1.0f);
    double lastMessageTime = (double) nodeArray[nodeArray.size()-1].point.x;
    lastMessage.setTimeStamp(lastMessageTime);
    midiSequence.addEvent(lastMessage, lastMessageTime);

    return midiSequence;
}


juce::MidiMessageSequence renderPathstringsToMidiSequence(std::vector<juce::String> pathStrings)
{
    if (pathStrings.size() == 0) return {};

    std::vector<pathHelper::NodeArray> pathsAsNodeArrays;
    for (auto pathString : pathStrings)
    {
        pathsAsNodeArrays.push_back(pathHelper::stringToNodeArray(pathString));
    }

    juce::MidiMessageSequence midiSequence = renderNodeArrayToMidiSequence(pathsAsNodeArrays[0]);

    return midiSequence;
}


