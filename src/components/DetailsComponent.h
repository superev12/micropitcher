
#pragma once

class DetailsComponent : public juce::Component
{
public:
    DetailsComponent()
    {
    }

    ~DetailsComponent()
    {
    }

    void paint(juce::Graphics& g) override
    {
        auto area = getLocalBounds();
        g.setColour(juce::Colours::purple);
        g.fillRect(area);
    }

    void resized() override
    {
    }
};

