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
#include "../PathHelper.h"

const float lineStrokeWidth = 5.0f;
const float pointHandleRadius = 5.0f;
const float pointHandleDiameter = pointHandleRadius * 2;
const float pointHandleStrokeWeight = 5.0f;
const float handleLineStrokeWeight = 2.0f;
//[/MiscUserDefs]

//==============================================================================
GraphComponent::GraphComponent (juce::ValueTree& state) : valueTree(state)
{
    //[Constructor_pre] You can add your own custom stuff here..
    valueTree.addListener(this);

    // Add ValueTree for graph
    juce::ValueTree graphState (TreeValues::graphIdentifier);
    valueTree.addChild(graphState, -1, nullptr);
    writeSelectedPathToValueTree(selectedPathIndex);

    readPathsFromValueTree();

    //[/Constructor_pre]


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

    //[UserPaint] Add your own custom painting code here..
    int numberOfPaths = pathStrings.size();
    for (int i = 0; i < numberOfPaths; i++)
    {
        juce::Path path;
        path.restoreFromString(pathStrings[i]);
        juce::Colour strokeColour = juce::Colour (0xff4ea52a);
        g.setColour (strokeColour);


        auto nodeArray = pathHelper::stringToNodeArray(pathStrings[i]);
        if (nodeArray.size() == 1)
        {
            auto node = nodeArray[0];
            g.fillEllipse(node.point.x - lineStrokeWidth/2, node.point.y - lineStrokeWidth/2, lineStrokeWidth, lineStrokeWidth);
        } else {
            g.strokePath (path, juce::PathStrokeType (5.000f), juce::AffineTransform::translation(0.0f, 0.0f));
        }

        if (selectedPathIndex == i)
        {
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

static int getClickedHandleLIndex(juce::String selectedPathString, juce::Point<float>mousePoint)
{
    int clickedIndex = -1;

    auto nodeArray = pathHelper::stringToNodeArray(selectedPathString);

    for (int nodeIndex = 0; nodeIndex < nodeArray.size(); nodeIndex++)
    {
        if
        (
            nodeArray[nodeIndex].handleL.getDistanceFrom(mousePoint)
                <
            pointHandleRadius+pointHandleStrokeWeight/2
        )
        {
            clickedIndex = nodeIndex;
        }
    }

    return clickedIndex;
}

static int getClickedHandleRIndex(juce::String selectedPathString, juce::Point<float>mousePoint)
{
    int clickedIndex = -1;
    auto nodeArray = pathHelper::stringToNodeArray(selectedPathString);

    for (int nodeIndex = 0; nodeIndex < nodeArray.size(); nodeIndex++)
    {
        if
        (
            nodeArray[nodeIndex].handleR.getDistanceFrom(mousePoint)
                <
            pointHandleRadius+pointHandleStrokeWeight/2
        )
        {
            clickedIndex = nodeIndex;
        }
    }

    return clickedIndex;
}

static int getClickedNodeIndex(juce::String selectedPathString, juce::Point<float>mousePoint)
{
    int clickedIndex = -1;
    auto nodeArray = pathHelper::stringToNodeArray(selectedPathString);

    for (int nodeIndex = 0; nodeIndex < nodeArray.size(); nodeIndex++)
    {
        if
        (
            nodeArray[nodeIndex].point.getDistanceFrom(mousePoint)
                <
            pointHandleRadius+pointHandleStrokeWeight/2
        )
        {
            clickedIndex = nodeIndex;
        }
    }

    return clickedIndex;
}

static int getClickedPathIndex(std::vector<juce::String> pathStrings, juce::Point<float>mousePoint)
{
    int selectedPathIndex = -1;
    for (int pathIndex = 0; pathIndex < pathStrings.size(); pathIndex++)
    {
        auto nodeArray = pathHelper::stringToNodeArray(pathStrings[pathIndex]);
        float distanceToPoint;
        if (nodeArray.size() == 1)
        {
            distanceToPoint = mousePoint.getDistanceFrom(nodeArray[0].point);
        } else {
            juce::Path path;
            path.restoreFromString(pathStrings[pathIndex]);
            juce::Point<float> nearestPointToMouse;
            path.getNearestPoint(mousePoint, nearestPointToMouse);
            distanceToPoint = mousePoint.getDistanceFrom(nearestPointToMouse);
        }
        if (distanceToPoint < 5.0f) selectedPathIndex = pathIndex;
        //DBG(juce::String(pathIndex) + juce::String(" e ") + juce::String(distanceToPoint));
    }

    return selectedPathIndex;
}

void GraphComponent::mouseDown (const juce::MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...

    auto mousePoint = e.getPosition().toFloat();

    switch (toolMode)
    {
        case (TreeValues::ToolModeValues::POINTER):
        {
            DBG("clicked in pointer mode");
            int clickedPathIndex = getClickedPathIndex(pathStrings, mousePoint);

            if (selectedPathIndex == -1)
            {
                // Nothing is currently selected
                if (clickedPathIndex != selectedPathIndex)
                {
                    // A new path was clicked
                    writeSelectedPathToValueTree(clickedPathIndex);
                }
                else
                {
                    // Nothing was clicked, do nothing
                }
            }
            else 
            {
                // A path is currently selected
                auto selectedPathString = pathStrings[selectedPathIndex];
                int clickedHandleLIndex = getClickedHandleLIndex(selectedPathString, mousePoint); 
                int clickedHandleRIndex = getClickedHandleRIndex(selectedPathString, mousePoint); 
                int clickedNodeIndex = getClickedNodeIndex(selectedPathString, mousePoint);

                // Special case to prioritise the node at the end of paths
                if (clickedNodeIndex == 0) clickedHandleLIndex = -1;
                if (clickedNodeIndex == pathHelper::getNumberOfNodes(selectedPathString)-1) clickedHandleRIndex = -1;

                if (clickedHandleLIndex != -1)
                {
                    // A left handle was clicked
                    grabbedPathIndex = selectedPathIndex;
                    grabbedNodeIndex = clickedHandleLIndex;
                    grabbedHandleType = handleType::LEFT;
                    interactionState = DRAGGING;
                }
                else if (clickedHandleRIndex != -1)
                {
                    // A right handle was clicked
                    grabbedPathIndex = selectedPathIndex;
                    grabbedNodeIndex = clickedHandleRIndex;
                    grabbedHandleType = handleType::RIGHT;
                    interactionState = DRAGGING;
                }
                else if (clickedNodeIndex != -1)
                {
                    // A node was clicked
                    grabbedPathIndex = selectedPathIndex;
                    grabbedNodeIndex = clickedNodeIndex;
                    grabbedHandleType = handleType::NODE;
                    interactionState = DRAGGING;
                }
                else if (clickedPathIndex == -1)
                {
                    // Empty space clicked, deselect current
                    writeSelectedPathToValueTree(-1);
                }
                else if (clickedPathIndex != selectedPathIndex)
                {
                    // New path clicked, make new selection
                    writeSelectedPathToValueTree(clickedPathIndex);
                }
                else 
                {
                    // I have no idea what was clicked
                }
            }
            break;
        }

        case (TreeValues::ToolModeValues::PENCIL):
        {
            DBG("clicked in pencil mode");
            if (selectedPathIndex == -1)
            {
                // No path was selected, create new path at cursor
                auto newPathString = pathHelper::nodeArrayToString
                ({{
                    .point=mousePoint,
                    .handleL=mousePoint,
                    .handleR=mousePoint,
                }});
                pathStrings.push_back(newPathString);
                writeSelectedPathToValueTree(pathStrings.size() - 1);
                writePathsToValueTree();
            }
            else
            {
                // Path was selected, add node to path at cursor
                pathStrings[selectedPathIndex] = pathHelper::addNode(pathStrings[selectedPathIndex], mousePoint);
                writePathsToValueTree();
            }
            break;
        }
    }

    
    //pathStrings[0] = pathHelper::moveNode(pathStrings[0], 0, e.getPosition().toFloat());

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
        pathStrings[grabbedPathIndex] = pathHelper::moveNode(
            pathStrings[grabbedPathIndex],
            grabbedNodeIndex,
            mousePoint
        );
        break;
    case handleType::LEFT:
        pathStrings[grabbedPathIndex] = pathHelper::moveNodeHandleL(
            pathStrings[grabbedPathIndex],
            grabbedNodeIndex,
            mousePoint
        );
        break;
    case handleType::RIGHT:
        pathStrings[grabbedPathIndex] = pathHelper::moveNodeHandleR(
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
    if (id == TreeValues::selectedPathIdentifier)
    {
        selectedPathIndex = (int) valueTree.getProperty(id);
    }

    if (id == TreeValues::toolModeIdentifier)
    {
        toolMode = static_cast<TreeValues::ToolModeValues>((int) valueTree.getProperty(id));
    }
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
}

void GraphComponent::writeSelectedPathToValueTree(int newSelectedPathIndex)
{
    selectedPathIndex = newSelectedPathIndex;
    valueTree.setProperty(TreeValues::selectedPathIdentifier, selectedPathIndex, nullptr);
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

