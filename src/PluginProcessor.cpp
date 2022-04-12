
#include "PluginProcessor.h"
#include "PluginEditor.h"

constexpr bool shouldUseGenericEditor = false;

MicropitcherProcessor::MicropitcherProcessor()
{
}

void MicropitcherProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                                   juce::MidiBuffer& midiMessages)

{
    juce::ignoreUnused(midiMessages);

    buffer.clear();
}

juce::AudioProcessorEditor* MicropitcherProcessor::createEditor()
{
    if (shouldUseGenericEditor)
        return new juce::GenericAudioProcessorEditor(*this);
    else
        return new MicropitcherEditor(*this);
}

void MicropitcherProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    //Serializes your parameters, and any other potential data into an XML:

    juce::ValueTree params("Params");

    /*
    for (auto& param: getParameters())
    {
        juce::ValueTree paramTree(PluginHelpers::getParamID(param));
        paramTree.setProperty("Value", param->getValue(), nullptr);
        params.appendChild(paramTree, nullptr);
    }

    juce::ValueTree pluginPreset("MyPlugin");
    pluginPreset.appendChild(params, nullptr);
    */
    //This a good place to add any non-parameters to your preset

    //copyXmlToBinary(*pluginPreset.createXml(), destData);
}

void MicropitcherProcessor::setStateInformation(const void* data,
                                                          int sizeInBytes)
{
    //Loads your parameters, and any other potential data from an XML:

    /*
    auto xml = getXmlFromBinary(data, sizeInBytes);

    if (xml != nullptr)
    {
        auto preset = juce::ValueTree::fromXml(*xml);
        auto params = preset.getChildWithName("Params");

        for (auto& param: getParameters())
        {
            auto paramTree = params.getChildWithName(PluginHelpers::getParamID(param));

            if (paramTree.isValid())
                param->setValueNotifyingHost(paramTree["Value"]);
        }

        //Load your non-parameter data now
    }
    */
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MicropitcherProcessor();
}
