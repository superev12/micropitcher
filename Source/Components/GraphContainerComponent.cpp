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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "GraphContainerComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
GraphContainerComponent::GraphContainerComponent (juce::ValueTree& state) : valueTree(state)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    juce__viewport.reset (new juce::Viewport ("new viewport"));
    addAndMakeVisible (juce__viewport.get());
    juce__viewport->setScrollBarsShown (true, true);
    juce__viewport->setViewedComponent (new GraphComponent(valueTree));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    valueTree.addListener(this);
    //[/Constructor]
}

GraphContainerComponent::~GraphContainerComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    juce__viewport = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void GraphContainerComponent::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    g.fillAll (backgroundColour);
    //[/UserPaint]
}

void GraphContainerComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    juce__viewport->setBounds ((getWidth() / 2) - ((getWidth() - 20) / 2), (getHeight() / 2) + -2 - ((getHeight() - 20) / 2), getWidth() - 20, getHeight() - 20);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void GraphContainerComponent::valueTreePropertyChanged(juce::ValueTree& tree, const juce::Identifier& id)
{
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="GraphContainerComponent"
                 componentName="" parentClasses="public juce::Component" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
  <VIEWPORT name="new viewport" id="1b7864cd13d512e6" memberName="juce__viewport"
            virtualName="" explicitFocusOrder="0" pos="0Cc -1.5Cc 20M 20M"
            vscroll="0" hscroll="0" scrollbarThickness="8" contentType="2"
            jucerFile="" contentClass="GraphComponent" constructorParams=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

