#include <JuceHeader.h>

namespace graphHelper
{
    struct Node
    {
        juce::Point<float> point;
        juce::Point<float> handleL;
        juce::Point<float> handleR;
    };

    std::vector<juce::String>splitString(juce::String& string, char splitChar)
    {
        auto remainingString = string;
        std::vector<juce::String> splitStrings = {};

        juce::String noSpaceString = "stringwithNoSpaces!";


        while (true)
        {
            int splitIndex = remainingString.indexOfChar(splitChar);
            if (splitIndex == -1)
            {
                // There was no space in the string
                splitStrings.push_back(juce::String(remainingString));
                break;
                //return splitStrings;
            }

            if (splitIndex+1 >= remainingString.length())
            {
                // There was nothing after the space
                splitStrings.push_back(juce::String(remainingString.substring(0, splitIndex)));
                break;
                //return splitStrings;
            }
                

            splitStrings.push_back(juce::String(remainingString.substring(0, splitIndex)));
            remainingString = juce::String(remainingString.substring(splitIndex+1, remainingString.length()));
        }
        return splitStrings;
    }


    std::vector<Node> stringToNodeArray(juce::String& pathString)
    {
        std::vector<Node> nodeArray = {};

        auto splitValues = splitString(pathString, ' ');
        if (splitValues[0] != "a") return {};
        if (splitValues[1] != "m") return {};
        const float originX = splitValues[2].getFloatValue();
        const float originY = splitValues[3].getFloatValue();

        if (splitValues.size() == 4)
        {
            // path is a single point
            nodeArray.push_back(
                {
                    .point = juce::Point<float>(originX, originY),
                    .handleL = juce::Point<float>(originX, originY),
                    .handleR = juce::Point<float>(originX, originY),
                }
            );
            return nodeArray;
        }

        if (splitValues[4] != "c") return {};
        const float originRHandleX = splitValues[5].getFloatValue();
        const float originRHandleY = splitValues[6].getFloatValue();

        // first point in path (has no left handle)
        nodeArray.push_back(
                {
                    .point = juce::Point<float>( originX,  originY),
                    .handleL = juce::Point<float>( originX,  originY),
                    .handleR = juce::Point<float>( originRHandleX,  originRHandleY),
                }
        );

        int nodeStartIndex = 7;

        while (nodeStartIndex + 5 < splitValues.size())
        {
            const float currentLHandleX = splitValues[nodeStartIndex].getFloatValue();
            const float currentLHandleY = splitValues[nodeStartIndex+1].getFloatValue();
            const float currentPointX = splitValues[nodeStartIndex+2].getFloatValue();
            const float currentPointY = splitValues[nodeStartIndex+3].getFloatValue();
            const float currentRHandleX = splitValues[nodeStartIndex+4].getFloatValue();
            const float currentRHandleY = splitValues[nodeStartIndex+5].getFloatValue();
            nodeArray.push_back(
                {
                    .point = juce::Point<float>( currentPointX,  currentPointY),
                    .handleL = juce::Point<float>( currentLHandleX,  currentLHandleY),
                    .handleR = juce::Point<float>( currentRHandleX,  currentRHandleY),
                }
            );
            nodeStartIndex += 6;
        }

        // final point in path (has no right handle)
        const float lastLHandleX = splitValues[nodeStartIndex].getFloatValue();
        const float lastLHandleY = splitValues[nodeStartIndex+1].getFloatValue();
        const float lastPointX = splitValues[nodeStartIndex+2].getFloatValue();
        const float lastPointY = splitValues[nodeStartIndex+3].getFloatValue();
        
        nodeArray.push_back(
            {
                .point = juce::Point<float>( lastPointX,  lastPointY),
                .handleL = juce::Point<float>( lastLHandleX,  lastLHandleY),
                .handleR = juce::Point<float>( lastPointX,  lastPointY),
            }
        );
        
        
        return nodeArray;
    }

    juce::String nodeArrayToString(std::vector<Node> nodeArray)
    {
        juce::String pathString ("");
        
        auto firstNode = nodeArray[0];
        pathString += juce::String("a m ");
        pathString += juce::String(firstNode.point.x);
        pathString += juce::String(" ");
        pathString += juce::String(firstNode.point.y);

        if (nodeArray.size() == 1) return pathString;

        pathString += juce::String(" c ");
        pathString += juce::String(firstNode.handleR.x);
        pathString += juce::String(" ");
        pathString += juce::String(firstNode.handleR.y);
        pathString += juce::String(" ");

        for (int i = 1; i < nodeArray.size() - 1; i++)
        {
            auto currentNode = nodeArray[i];

            pathString += juce::String(currentNode.handleL.x);
            pathString += juce::String(" ");
            pathString += juce::String(currentNode.handleL.y);
            pathString += juce::String(" ");
            pathString += juce::String(currentNode.point.x);
            pathString += juce::String(" ");
            pathString += juce::String(currentNode.point.y);
            pathString += juce::String(" ");
            pathString += juce::String(currentNode.handleR.x);
            pathString += juce::String(" ");
            pathString += juce::String(currentNode.handleR.y);
            pathString += juce::String(" ");
        }

        auto lastNode = nodeArray[nodeArray.size() - 1];

        pathString += juce::String(lastNode.handleL.x);
        pathString += juce::String(" ");
        pathString += juce::String(lastNode.handleL.y);
        pathString += juce::String(" ");
        pathString += juce::String(lastNode.point.x);
        pathString += juce::String(" ");
        pathString += juce::String(lastNode.point.y);

        return pathString;
    }

    // Test cases
    // `a m 123 456` -> `1`
    // `a m 123 456 c 123 456 789 123 456 789` -> `2`
    // `a m 123 456 c 123 456 789 123 456 789 123 456 789 123 456 789` -> `3`
    // `a m 123 456 c 123 456 789 123 456 789 123` -> `-1`
    // `123 456 c 123 456 789 123 456 789` -> `-1`
    int getNumberOfNodes(juce::String& pathString)
    {
        std::vector<Node> nodeArray = stringToNodeArray(pathString);

        return nodeArray.size();
    }

    // Test cases
    // `a m 123 456 c 123 456 789 123 456 789`, `2` -> `(456, 789)`
    // `a m 123 456 c 123 456 789 123 456 789 123 456 789 123 456 789`, `7` -> `undefined?`
    // `a m 123 456 c 123 456 789 123 456 789 123` -> `undefined?`
    // `123 456 c 123 456 789 123 456 789` -> `undefined?`
    juce::Point<float> getNodePosition(juce::String& pathString, int index)
    {
        std::vector<Node> nodeArray = stringToNodeArray(pathString);
        auto nodeAtIndex = nodeArray[index];
        return juce::Point<float>(nodeAtIndex.point.x, nodeAtIndex.point.y);
    }

    // Test cases
    // `a m 123 456` -> `1`
    // `a m 123 456 c 123 456 789 123 456 789` -> `(123, 456), (456, 789)`
    // `a m 123 456 c 123 456 789 123 456 789 123 456 789 123 999 111` -> `(123, 456), (456, 789), (999, 111)`
    // `a m 123 456 c 123 456 789 123 456 789 123` -> `-1`
    // `123 456 c 123 456 789 123 456 789` -> `-1`
    std::vector<juce::Point<float>> getNodePositions(juce::String& pathString)
    {
        std::vector<juce::Point<float>> points;
        std::vector<Node> nodeArray = stringToNodeArray(pathString);
        
        for (int i = 0; i < nodeArray.size(); i++)
        {
            points.push_back(
                juce::Point<float>(nodeArray[i].point.x, nodeArray[i].point.y)
            );
        }
        return points;
    }


    // Test cases
    // `a m 123 456`, `0`, `(123, 432)` -> `a m 123 432`
    // `a m 123 456`, `1`, `(123, 432)` -> `a m 123 456`
    // `a m 123 456 c 123 456 789 123 456 789`, `1`, `(0, 0)` -> `a m 123 456 c 123 456 789 123 0 0`
    // `a m 123 456 c 123 456 789 123 456 789 123 456 789 123 999 111` -> `(123, 456), (456, 789), (999, 111)`
    // `a m 123 456 c 123 456 789 123 456 789 123` -> `-1`
    // `123 456 c 123 456 789 123 456 789` -> `-1`
    juce::String moveNode(juce::String& pathString, int nodeIndex, juce::Point<float> newPosition)
    {
        std::vector<Node> nodeArray = stringToNodeArray(pathString);
        nodeArray[nodeIndex].point.x = newPosition.x;
        nodeArray[nodeIndex].point.y = newPosition.y;
        return nodeArrayToString(nodeArray);
    }

    juce::String moveNodeHandleL(juce::String& pathString, int nodeIndex, juce::Point<float> newPosition)
    {
        std::vector<Node> nodeArray = stringToNodeArray(pathString);
        nodeArray[nodeIndex].handleL.x = newPosition.x;
        nodeArray[nodeIndex].handleL.y = newPosition.y;
        return nodeArrayToString(nodeArray);
    }

    juce::String moveNodeHandleR(juce::String& pathString, int nodeIndex, juce::Point<float> newPosition)
    {
        std::vector<Node> nodeArray = stringToNodeArray(pathString);
        nodeArray[nodeIndex].handleR.x = newPosition.x;
        nodeArray[nodeIndex].handleR.y = newPosition.y;
        return nodeArrayToString(nodeArray);
    }
}

