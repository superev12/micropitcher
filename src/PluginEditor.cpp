#include "PluginProcessor.h"
#include "PluginEditor.h"

MeeQAudioProcessorEditor::MeeQAudioProcessorEditor(MeeQAudioProcessor& p)
    : AudioProcessorEditor(&p)
{
    setSize(400, 300);
}

void MeeQAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

