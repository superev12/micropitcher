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

#include "ToolbarComponent.h"
#include "../TreeValues.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
static juce::Identifier propertyName("button");
//[/MiscUserDefs]

//==============================================================================
ToolbarComponent::ToolbarComponent (juce::ValueTree& state) : valueTree(state)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    juce__textButton.reset (new juce::TextButton ("new button"));
    addAndMakeVisible (juce__textButton.get());
    juce__textButton->setButtonText (TRANS("Pointer"));
    juce__textButton->addListener (this);

    juce__textButton2.reset (new juce::TextButton ("new button"));
    addAndMakeVisible (juce__textButton2.get());
    juce__textButton2->setButtonText (TRANS("Pencil"));
    juce__textButton2->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ToolbarComponent::~ToolbarComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    juce__textButton = nullptr;
    juce__textButton2 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ToolbarComponent::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colours::red);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ToolbarComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    juce__textButton->setBounds (0, 8, proportionOfWidth (1.0000f), 24);
    juce__textButton2->setBounds (0, 40, proportionOfWidth (1.0000f), 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ToolbarComponent::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == juce__textButton.get())
    {
        //[UserButtonCode_juce__textButton] -- add your button handler code here..
        valueTree.setProperty(TreeValues::toolModeIdentifier, TreeValues::ToolModeValues::POINTER, nullptr);
        //[/UserButtonCode_juce__textButton]
    }
    else if (buttonThatWasClicked == juce__textButton2.get())
    {
        //[UserButtonCode_juce__textButton2] -- add your button handler code here..
        valueTree.setProperty(TreeValues::toolModeIdentifier, TreeValues::ToolModeValues::PENCIL, nullptr);
        //[/UserButtonCode_juce__textButton2]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ToolbarComponent" componentName=""
                 parentClasses="public juce::Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffff0000"/>
  <TEXTBUTTON name="new button" id="b7150a4fe795af28" memberName="juce__textButton"
              virtualName="" explicitFocusOrder="0" pos="0 8 100% 24" buttonText="new button1"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="9573603d4ba35de7" memberName="juce__textButton2"
              virtualName="" explicitFocusOrder="0" pos="0 40 100% 24" buttonText="new button2"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

