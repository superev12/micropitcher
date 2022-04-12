#include "PluginProcessor.h"
#include "PluginEditor.h"

MicropitcherEditor::MicropitcherEditor(MicropitcherProcessor& p)
    : AudioProcessorEditor(&p)
{
    setSize(400, 300);
}

void MicropitcherEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

