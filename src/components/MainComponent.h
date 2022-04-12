#pragma once

#include "ToolbarComponent.h"
#include "CentreComponent.h"
#include "DetailsComponent.h"

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

        addAndMakeVisible(toolbarComponent);
        addAndMakeVisible(centreComponent);
        addAndMakeVisible(detailsComponent);
    }

    void resized() override
    {
        auto area = getLocalBounds();
        toolbarComponent.setBounds(area.removeFromLeft(40));
        detailsComponent.setBounds(area.removeFromRight(150));
        centreComponent.setBounds(area);


    }
private:
    ToolbarComponent toolbarComponent;
    CentreComponent centreComponent;
    DetailsComponent detailsComponent;


};

