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

#include "GraphComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "../TreeValues.h"
#include "GraphHelper.h"
//[/MiscUserDefs]

//==============================================================================
GraphComponent::GraphComponent (juce::ValueTree& state) : valueTree(state)
{
    //[Constructor_pre] You can add your own custom stuff here..
    valueTree.addListener(this);

    // Add ValueTree for graph
    juce::ValueTree graphState (TreeValues::graphIdentifier);
    valueTree.addChild(graphState, -1, nullptr);

    // Add Test path to graph valueTree

    juce::ValueTree pathTree1 (TreeValues::pathTreeIdentifier);
    pathTree1.setProperty(TreeValues::pathStringIdentifier, "a m 274.9234 204 c 312 178 320 218 368 202 432 186 472 242 362 292", nullptr);
    valueTree.getChildWithName(TreeValues::graphIdentifier).addChild(pathTree1, 0, nullptr);

    juce::ValueTree pathTree2 (TreeValues::pathTreeIdentifier);
    pathTree2.setProperty(TreeValues::pathStringIdentifier, "a m 10 10", nullptr);
    valueTree.getChildWithName(TreeValues::graphIdentifier).addChild(pathTree2, 1, nullptr);

    readPathsFromValueTree();

    //graphHelper::getNumberOfNodes(pathStrings[0]);
    //[/Constructor_pre]

    /*
    internalPath1.setUsingNonZeroWinding (false);
    internalPath1.startNewSubPath (274.0f, 204.0f);
    internalPath1.cubicTo (312.0f, 178.0f, 320.0f, 218.0f, 368.0f, 202.0f);
    internalPath1.cubicTo (432.0f, 186.0f, 472.0f, 242.0f, 362.0f, 292.0f);
    internalPath1.lineTo (234.0f, 342.0f);
    */


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

GraphComponent::~GraphComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void GraphComponent::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff323e44));

    {
        float x = 244.0f, y = 220.0f, width = 100.0f, height = 100.0f;
        juce::Colour fillColour = juce::Colour (0xffa52aa4);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
    }

    {
        float x = 0, y = 0;
        juce::Colour strokeColour = juce::Colour (0xff4ea52a);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.strokePath (internalPath1, juce::PathStrokeType (5.000f), juce::AffineTransform::translation(x, y));
    }

    //[UserPaint] Add your own custom painting code here..
    int numberOfPaths = pathStrings.size();
    for (int i = 0; i < numberOfPaths; i++)
    {
        juce::Path path;
        path.restoreFromString(pathStrings[i]);
        juce::Colour strokeColour = juce::Colour (0xff4ea52a);
        g.setColour (strokeColour);
        g.strokePath (path, juce::PathStrokeType (5.000f), juce::AffineTransform::translation(0.0f, 0.0f));

        // Also draw circles at the nodes on the path
        /*
        auto nodePositions = graphHelper::getNodePositions(pathStrings[i]);
        for (int j = 0; j < nodePositions.size(); j++)
        {
            auto nodePosition = nodePositions[j];
            drawNodePoint(g, nodePosition);
        }
        */

        auto nodeArray = graphHelper::stringToNodeArray(pathStrings[i]);

        for (int j = 0; j < nodeArray.size(); j++)
        {
            auto nodePosition = nodeArray[j].point;
            auto nodeHandleLPosition = nodeArray[j].handleL;
            auto nodeHandleRPosition = nodeArray[j].handleR;

            drawNodeHandle(g, nodePosition, nodeHandleLPosition);
            drawNodeHandle(g, nodePosition, nodeHandleRPosition);
            drawNodePoint(g, nodePosition);
        }


    }


    //[/UserPaint]
}

void GraphComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void GraphComponent::moved()
{
    //[UserCode_moved] -- Add your code here...
    //[/UserCode_moved]
}

void GraphComponent::mouseDown (const juce::MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...

    auto mousePoint = e.getPosition().toFloat();

    // get node clicked
    for (int pathIndex = 0; pathIndex < pathStrings.size(); pathIndex++)
    {
        auto pathString = pathStrings[pathIndex];
        auto nodeArray = graphHelper::stringToNodeArray(pathString);

        for (int nodeIndex = 0; nodeIndex < nodeArray.size(); nodeIndex++)
        {
            if
            (
                nodeArray[nodeIndex].point.getDistanceFrom(mousePoint)
                    <
                pointHandleRadius+pointHandleStrokeWeight/2
            )
            {
                grabbedPathIndex = pathIndex;
                grabbedNodeIndex = nodeIndex;
                grabbedHandleType = handleType::NODE;
                //DBG(juce::String::formatted("setting grabbedHandleType to %i", grabbedHandleType));
            }
            else if
            (
                nodeArray[nodeIndex].handleL.getDistanceFrom(mousePoint)
                    <
                pointHandleRadius+pointHandleStrokeWeight/2
            )
            {
                grabbedPathIndex = pathIndex;
                grabbedNodeIndex = nodeIndex;
                grabbedHandleType = handleType::LEFT;
            }
            else if
            (
                nodeArray[nodeIndex].handleR.getDistanceFrom(mousePoint)
                    <
                pointHandleRadius+pointHandleStrokeWeight/2
            )
            {
                grabbedPathIndex = pathIndex;
                grabbedNodeIndex = nodeIndex;
                grabbedHandleType = handleType::RIGHT;
            }
        }
    }

    interactionState = DRAGGING;

    
    //pathStrings[0] = graphHelper::moveNode(pathStrings[0], 0, e.getPosition().toFloat());

    repaint();
    //[/UserCode_mouseDown]
}

void GraphComponent::mouseDrag (const juce::MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...
    if (grabbedPathIndex == -1 || grabbedNodeIndex == -1) return;

    auto mousePoint = e.getPosition().toFloat();

    //DBG(juce::String::formatted("moving node %i, handle %i", grabbedNodeIndex, grabbedHandleType));
    switch(grabbedHandleType)
    {
    case handleType::NODE:
        //DBG(juce::String::formatted("moving node %i", grabbedNodeIndex));
        pathStrings[grabbedPathIndex] = graphHelper::moveNode(
            pathStrings[grabbedPathIndex],
            grabbedNodeIndex,
            mousePoint
        );
        break;
    case handleType::LEFT:
        pathStrings[grabbedPathIndex] = graphHelper::moveNodeHandleL(
            pathStrings[grabbedPathIndex],
            grabbedNodeIndex,
            mousePoint
        );
        break;
    case handleType::RIGHT:
        pathStrings[grabbedPathIndex] = graphHelper::moveNodeHandleR(
            pathStrings[grabbedPathIndex],
            grabbedNodeIndex,
            mousePoint
        );
        break;
    }

    repaint();
    //[/UserCode_mouseDrag]
}

void GraphComponent::mouseUp (const juce::MouseEvent& e)
{
    //[UserCode_mouseUp] -- Add your code here...
    interactionState = NEUTRAL;

    grabbedPathIndex = -1;
    grabbedNodeIndex = -1;

    writePathsToValueTree();
    //[/UserCode_mouseUp]
}

void GraphComponent::mouseWheelMove (const juce::MouseEvent& e, const juce::MouseWheelDetails& wheel)
{
    //[UserCode_mouseWheelMove] -- Add your code here...
    //[/UserCode_mouseWheelMove]
}

void GraphComponent::modifierKeysChanged (const juce::ModifierKeys& modifiers)
{
    //[UserCode_modifierKeysChanged] -- Add your code here...
    //[/UserCode_modifierKeysChanged]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void GraphComponent::valueTreePropertyChanged(juce::ValueTree& tree, const juce::Identifier& id)
{

}

void GraphComponent::readPathsFromValueTree()
{
    pathStrings = {};

    int numberOfPaths = valueTree.getChildWithName(TreeValues::graphIdentifier).getNumChildren();
    for (int i = 0; i < numberOfPaths; i++)
    {
        pathStrings.push_back(valueTree.getChildWithName(TreeValues::graphIdentifier).getChild(i).getProperty(TreeValues::pathStringIdentifier));
    }
}

void GraphComponent::writePathsToValueTree()
{
    auto graphTree = valueTree.getChildWithName(TreeValues::graphIdentifier);
    //graphTree.removeAllChildren(nullptr);

    int numberOfPaths = pathStrings.size();
    for (int i = 0; i < numberOfPaths; i++)
    {
        juce::String pathStringInValueTree = graphTree
            .getChild(i)
            .getProperty(TreeValues::pathStringIdentifier)
            .toString();
        if (pathStringInValueTree == pathStrings[i]) continue;

        juce::ValueTree pathTree (TreeValues::pathTreeIdentifier);
        pathTree.setProperty(TreeValues::pathStringIdentifier, pathStrings[i], nullptr);
        graphTree.removeChild(i, nullptr);
        graphTree.addChild(pathTree, i, nullptr);
    }
    DBG("writing them paths to the value tree");
}

void GraphComponent::drawNodePoint(juce::Graphics& g, juce::Point<float> point)
{
    g.setColour (juce::Colour(0xff323e44));
    g.fillEllipse(point.x - pointHandleRadius, point.y - pointHandleRadius, pointHandleDiameter, pointHandleDiameter);
    g.setColour (juce::Colour (0xff4ea52a));
    g.drawEllipse(point.x - pointHandleRadius, point.y - pointHandleRadius, pointHandleDiameter, pointHandleDiameter, pointHandleStrokeWeight);
}

void GraphComponent::drawNodeHandle(juce::Graphics& g, juce::Point<float> originPoint, juce::Point<float> handlePoint)
{
    juce::Line<float> handleLine (originPoint, handlePoint);
    g.drawLine(handleLine, handleLineStrokeWeight);
    drawNodePoint(g, handlePoint);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="GraphComponent" componentName=""
                 parentClasses="public juce::Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <METHODS>
    <METHOD name="mouseDown (const juce::MouseEvent&amp; e)"/>
    <METHOD name="mouseDrag (const juce::MouseEvent&amp; e)"/>
    <METHOD name="mouseUp (const juce::MouseEvent&amp; e)"/>
    <METHOD name="mouseWheelMove (const juce::MouseEvent&amp; e, const juce::MouseWheelDetails&amp; wheel)"/>
    <METHOD name="modifierKeysChanged (const juce::ModifierKeys&amp; modifiers)"/>
    <METHOD name="moved()"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff323e44">
    <ROUNDRECT pos="244 220 100 100" cornerSize="10.0" fill="solid: ffa52aa4"
               hasStroke="0"/>
    <PATH pos="0 0 100 100" fill="solid: a5962a" hasStroke="1" stroke="5, mitered, butt"
          strokeColour="solid: ff4ea52a" nonZeroWinding="0">s 274 204 c 312 178 320 218  368 202 c 432 186 472 242  362 292 l 234 342</PATH>
  </BACKGROUND>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

