#include "PluginProcessor.h"
#include "PluginEditor.h"

MeeQAudioProcessorEditor::MeeQAudioProcessorEditor(
    MeeQAudioProcessor& p)
    : AudioProcessorEditor(&p)
{
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 50);
    addAndMakeVisible(gainSlider);
    setSize(600, 400);
}

void MeeQAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void MeeQAudioProcessorEditor::resized()
{
    gainSlider.setBounds(getWidth()/2-100, getHeight()/2-50,200,100);
}