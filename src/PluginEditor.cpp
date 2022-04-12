#include "PluginProcessor.h"
#include "PluginEditor.h"

MicropitcherEditor::MicropitcherEditor(MicropitcherProcessor& p)
    : AudioProcessorEditor(&p)
{
    auto area = getLocalBounds();
    setSize(400, 300);
    addAndMakeVisible(mainComponent);
}

void MicropitcherEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    //g.fillAll(juce::Colours::deeppink);

    
}

void MicropitcherEditor::resized()
{
    mainComponent.setBounds(0, 0, getWidth(), getHeight());

}

