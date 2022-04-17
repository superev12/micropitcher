/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MicropitcherAudioProcessorEditor::MicropitcherAudioProcessorEditor (MicropitcherAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), mainComponent()
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 400);
    setResizable(true, true);
    setResizeLimits(400, 400, 99999, 99999);
}

MicropitcherAudioProcessorEditor::~MicropitcherAudioProcessorEditor()
{
}

//==============================================================================
void MicropitcherAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::white);
    addAndMakeVisible(mainComponent);
}

void MicropitcherAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    mainComponent.setBounds(0, 0, getWidth(), getHeight());
}
