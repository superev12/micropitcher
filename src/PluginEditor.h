#pragma once

#include "PluginProcessor.h"
#include "components/MainComponent.h"

class MicropitcherEditor : public juce::AudioProcessorEditor
{
public:
    explicit MicropitcherEditor(MicropitcherProcessor&);
    ~MicropitcherEditor() {};

    void paint(juce::Graphics&) override;
    void resized() override;
private:
    MainComponent mainComponent;
};
