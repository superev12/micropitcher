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

#include "DetailsComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "../TreeValues.h"
#include "../PathHelper.h"
#include "../MidiProcessor.h"
//[/MiscUserDefs]

//==============================================================================
DetailsComponent::DetailsComponent (juce::ValueTree& state) : valueTree(state)
{
    //[Constructor_pre] You can add your own custom stuff here..
    valueTree.addListener(this);
    //[/Constructor_pre]

    juce__textEditor1.reset (new juce::TextEditor ("textEditor1"));
    addAndMakeVisible (juce__textEditor1.get());
    juce__textEditor1->setMultiLine (false);
    juce__textEditor1->setReturnKeyStartsNewLine (false);
    juce__textEditor1->setReadOnly (false);
    juce__textEditor1->setScrollbarsShown (true);
    juce__textEditor1->setCaretVisible (true);
    juce__textEditor1->setPopupMenuEnabled (true);
    // Shows Hz
    juce__textEditor1->setText (juce::String(""));

    juce__label.reset (new juce::Label ("text1",
                                        TRANS("Frequency (Hz)")));
    addAndMakeVisible (juce__label.get());
    juce__label->setFont (juce::Font (15.00f, juce::Font::plain));
    juce__label->setJustificationType (juce::Justification::centredRight);
    juce__label->setEditable (false, false, false);
    juce__label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__textEditor2.reset (new juce::TextEditor ("textEditor2"));
    addAndMakeVisible (juce__textEditor2.get());
    juce__textEditor2->setMultiLine (false);
    juce__textEditor2->setReturnKeyStartsNewLine (false);
    juce__textEditor2->setReadOnly (false);
    juce__textEditor2->setScrollbarsShown (true);
    juce__textEditor2->setCaretVisible (true);
    juce__textEditor2->setPopupMenuEnabled (true);
    // Shows MidiNote
    juce__textEditor2->setText (juce::String(""));

    juce__label2.reset (new juce::Label ("text1",
                                         TRANS("Midi Number\n")));
    addAndMakeVisible (juce__label2.get());
    juce__label2->setFont (juce::Font (15.00f, juce::Font::plain));
    juce__label2->setJustificationType (juce::Justification::centredRight);
    juce__label2->setEditable (false, false, false);
    juce__label2->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label2->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label3.reset (new juce::Label ("text1",
                                         TRANS("label text")));
    addAndMakeVisible (juce__label3.get());
    juce__label3->setFont (juce::Font (15.00f, juce::Font::plain));
    juce__label3->setJustificationType (juce::Justification::centred);
    juce__label3->setEditable (false, false, false);
    juce__label3->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label3->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__textEditor3.reset (new juce::TextEditor ("textEditor3"));
    //addAndMakeVisible (juce__textEditor3.get());
    juce__textEditor3->setMultiLine (false);
    juce__textEditor3->setReturnKeyStartsNewLine (false);
    juce__textEditor3->setReadOnly (false);
    juce__textEditor3->setScrollbarsShown (true);
    juce__textEditor3->setCaretVisible (true);
    juce__textEditor3->setPopupMenuEnabled (true);
    // Shows cents deviation
    juce__textEditor3->setText (juce::String(""));

    juce__label4.reset (new juce::Label ("text1",
                                         TRANS("Cents")));
    addAndMakeVisible (juce__label4.get());
    juce__label4->setFont (juce::Font (15.00f, juce::Font::plain));
    juce__label4->setJustificationType (juce::Justification::centredRight);
    juce__label4->setEditable (false, false, false);
    juce__label4->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label4->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    rerenderText();
    //[/Constructor]
}

DetailsComponent::~DetailsComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    juce__textEditor1 = nullptr;
    juce__label = nullptr;
    juce__textEditor2 = nullptr;
    juce__label2 = nullptr;
    juce__label3 = nullptr;
    juce__textEditor3 = nullptr;
    juce__label4 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void DetailsComponent::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //g.fillAll (juce::Colours::chartreuse);

    //[UserPaint] Add your own custom painting code here..
    g.fillAll (juce::Colour(238, 232, 213));
    //[/UserPaint]
}

void DetailsComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    juce__textEditor1->setBounds ((getWidth() / 2) - (100 / 2), 64, 100, 24);
    juce__label->setBounds (((getWidth() / 2) - (100 / 2)) + -160, 64, 100, 24);
    juce__textEditor2->setBounds ((getWidth() / 2) - (100 / 2), 98, 100, 24);
    juce__label2->setBounds (((getWidth() / 2) - (100 / 2)) + -160, 98, 100, 24);
    juce__label3->setBounds (((getWidth() / 2) - (100 / 2)) + 150 / 2 - (150 / 2), 32, 100, 24);
    juce__textEditor3->setBounds ((getWidth() / 2) - (100 / 2), 135, 100, 24);
    juce__label4->setBounds (((getWidth() / 2) - (100 / 2)) + -160, 135, 100, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void DetailsComponent::valueTreePropertyChanged(juce::ValueTree& tree, const juce::Identifier& id)
{
    DBG("the details component is rerendering text");
    rerenderText();

}

void DetailsComponent::rerenderText()
{
    int selectedPathIndex = (int) valueTree.getProperty(TreeValues::selectedPathIdentifier);
    TreeValues::ToolModeValues toolMode = static_cast<TreeValues::ToolModeValues>((int) valueTree.getProperty(TreeValues::toolModeIdentifier));

    juce::String toolString;
    if (toolMode == TreeValues::POINTER) toolString = juce::String("Pointer");
    if (toolMode == TreeValues::PENCIL) toolString = juce::String("Pencil");
        juce__textEditor1->setText (toolString);

    if (selectedPathIndex != -1)
        juce__textEditor2->setText (juce::String("Path ") + juce::String(selectedPathIndex));


    juce::String();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="DetailsComponent" componentName=""
                 parentClasses="public juce::Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff7fff00"/>
  <TEXTEDITOR name="textEditor1" id="6bf1c357078c20b2" memberName="juce__textEditor1"
              virtualName="" explicitFocusOrder="0" pos="0Cc 64 150 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="text1" id="8ed328a87b9f3b78" memberName="juce__label" virtualName=""
         explicitFocusOrder="0" pos="-160 64 150 24" posRelativeX="6bf1c357078c20b2"
         edTextCol="ff000000" edBkgCol="0" labelText="Frequency (Hz)"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
         italic="0" justification="34"/>
  <TEXTEDITOR name="textEditor2" id="97940ea2f76288bc" memberName="juce__textEditor2"
              virtualName="" explicitFocusOrder="0" pos="0Cc 98 150 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="text1" id="3a26edd64ab227dd" memberName="juce__label2"
         virtualName="" explicitFocusOrder="0" pos="-160 98 150 24" posRelativeX="6bf1c357078c20b2"
         edTextCol="ff000000" edBkgCol="0" labelText="Midi Number&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
         italic="0" justification="34"/>
  <LABEL name="text1" id="ad83dd3f45904e5e" memberName="juce__label3"
         virtualName="" explicitFocusOrder="0" pos="0Cc 32 150 24" posRelativeX="6bf1c357078c20b2"
         edTextCol="ff000000" edBkgCol="0" labelText="label text" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <TEXTEDITOR name="textEditor3" id="e65db50df74ed941" memberName="juce__textEditor3"
              virtualName="" explicitFocusOrder="0" pos="0Cc 135 150 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="text1" id="f42d4390f7472ce8" memberName="juce__label4"
         virtualName="" explicitFocusOrder="0" pos="-160 135 150 24" posRelativeX="6bf1c357078c20b2"
         edTextCol="ff000000" edBkgCol="0" labelText="Cents" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="34"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

