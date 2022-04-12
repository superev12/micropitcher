#pragma once

class MainComponent : public juce::Component
{
public:
    MainComponent()
    {
    }

    ~MainComponent() {};

    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::red);
        sideBar.setColour(juce::TextButton::buttonColourId, juce::Colours::yellow);
        addAndMakeVisible(sideBar);
    }

    void resized() override
    {
        auto area = getLocalBounds();
        sideBar.setBounds(area.removeFromLeft(15));


    }
private:
    juce::TextButton sideBar;
};

