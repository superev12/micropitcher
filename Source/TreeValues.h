#pragma once

#include <JuceHeader.h>

namespace TreeValues {
    static juce::Identifier graphIdentifier ("graph");
    static juce::Identifier pathTreeIdentifier ("pathTree");
    static juce::Identifier pathStringIdentifier ("pathString");
    static juce::Identifier selectedPathIdentifier ("selectedPath");

    static juce::Identifier toolModeIdentifier ("toolMode");
    enum ToolModeValues { POINTER, PENCIL };
}
