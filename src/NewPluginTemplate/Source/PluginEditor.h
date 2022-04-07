#pragma once

#include "PluginProcessor.h"

class MeeQAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit MeeQAudioProcessorEditor(MeeQAudioProcessor&);

    void paint(juce::Graphics&) override;
    void resized() override {}
};
