#pragma once

#include <juce_audio_utils/juce_audio_utils.h>

class MicropitcherProcessor : public juce::AudioProcessor
{
public:
    MicropitcherProcessor();

    // const flags
    bool hasEditor() const override { return true; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return true; }
    bool isMidiEffect() const override { return false; }
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override { return false; }
    void prepareToPlay(double sampleRate, int samplesPerBlock) override { juce::ignoreUnused(sampleRate, samplesPerBlock); };
    void releaseResources() override {};

    using AudioProcessor::processBlock;

    double getTailLengthSeconds() const override { return 0.0; }
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int index) { juce::ignoreUnused(index); }
    const juce::String getProgramName(int index) override { juce::ignoreUnused(index); return {}; }
    void changeProgramName(int index, const juce::String& newName) override { juce::ignoreUnused(index, newName); }
    const juce::String getName() const override { return JucePlugin_Name; }

    // Functions
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

};
