/*
  ==============================================================================

    PluginEditor.h
    Created: 23 Apr 2022 7:39:41pm
    Author:  evan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
//#include "PluginProcessor.h"
#include "Components/MainComponent.h"

//==============================================================================
/**
*/
class MicropitcherAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MicropitcherAudioProcessorEditor (MicropitcherAudioProcessor&, juce::ValueTree&);
    ~MicropitcherAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MicropitcherAudioProcessor& audioProcessor;
    juce::ValueTree valueTree;
    MainComponent mainComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MicropitcherAudioProcessorEditor)
};
