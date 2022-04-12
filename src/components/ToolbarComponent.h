#pragma once

class ToolbarComponent : public juce::Component
{
public:
    ToolbarComponent()
    {
    }

    ~ToolbarComponent()
    {
    }

    void paint(juce::Graphics& g) override
    {
        auto area = getLocalBounds();
        g.setColour(juce::Colours::orange);
        g.fillRect(area);
    }

    void resized() override
    {
    }
};

