/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.1.6

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "interactionStates.h"

enum class handleType {LEFT, NODE, RIGHT};
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class GraphComponent  : public juce::Component, public juce::ValueTree::Listener
{
public:
    //==============================================================================
    GraphComponent (juce::ValueTree&);
    ~GraphComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void valueTreePropertyChanged(juce::ValueTree&, const juce::Identifier&) override;
    void readPathsFromValueTree();
    void writePathsToValueTree();
    void writeSelectedPathToValueTree(int);
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void moved() override;
    void mouseDown (const juce::MouseEvent& e) override;
    void mouseDrag (const juce::MouseEvent& e) override;
    void mouseUp (const juce::MouseEvent& e) override;
    void mouseWheelMove (const juce::MouseEvent& e, const juce::MouseWheelDetails& wheel) override;
    void modifierKeysChanged (const juce::ModifierKeys& modifiers) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    juce::ValueTree valueTree;
    InteractionState interactionState = NEUTRAL;
    std::vector<juce::String> pathStrings;
    void drawNodePoint(juce::Graphics& g, juce::Point<float>);
    void drawNodeHandle(juce::Graphics& g, juce::Point<float>, juce::Point<float>);

    int selectedPathIndex = -1;
    int grabbedPathIndex = -1;
    int grabbedNodeIndex = -1;
    handleType grabbedHandleType = handleType::NODE;

    const float pointHandleRadius = 5.0f;
    const float pointHandleDiameter = pointHandleRadius * 2;
    const float pointHandleStrokeWeight = 5.0f;

    const float handleLineStrokeWeight = 2.0f;
    //[/UserVariables]

    //==============================================================================
    juce::Path internalPath1;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GraphComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

