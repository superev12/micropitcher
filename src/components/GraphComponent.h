
#pragma once

class GraphComponent : public juce::Component
{
public:
    GraphComponent()
    {
    }

    ~GraphComponent()
    {
    }

    void paint(juce::Graphics& g) override
    {
        auto area = getLocalBounds();
        g.setColour(juce::Colours::green);
        g.fillRect(area);
    }

    void resized() override
    {
    }
};

