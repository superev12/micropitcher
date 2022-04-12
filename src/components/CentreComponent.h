#pragma once

#include "GraphComponent.h"

class CentreComponent : public juce::Component
{
public:
    CentreComponent()
    {
    }

    ~CentreComponent()
    {
    }

    void paint(juce::Graphics& g) override
    {
        auto area = getLocalBounds();
        g.setColour(juce::Colours::white);
        g.fillRect(area);
        addAndMakeVisible(graphComponent);
    }

    void resized() override
    {
        auto area = getLocalBounds();
        graphComponent.setBounds(area.reduced(50));
    }
private:
    GraphComponent graphComponent;
};

