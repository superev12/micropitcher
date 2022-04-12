#pragma once

#include "PluginProcessor.h"

class MicropitcherEditor : public juce::AudioProcessorEditor
{
public:
    explicit MicropitcherEditor(MicropitcherProcessor&);

    void paint(juce::Graphics&) override;
    void resized() override {}
};
