/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/
#include <cmath>

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MidiProcessor.h"
#include "TreeValues.h"

//==============================================================================
MicropitcherAudioProcessor::MicropitcherAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    valueTree.addListener(this);

    valueTree.setProperty(TreeValues::toolModeIdentifier, TreeValues::ToolModeValues::POINTER, nullptr);
}

MicropitcherAudioProcessor::~MicropitcherAudioProcessor()
{
}

//==============================================================================
const juce::String MicropitcherAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MicropitcherAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MicropitcherAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MicropitcherAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MicropitcherAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MicropitcherAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MicropitcherAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MicropitcherAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MicropitcherAudioProcessor::getProgramName (int index)
{
    return {};
}

void MicropitcherAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MicropitcherAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void MicropitcherAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MicropitcherAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MicropitcherAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    double timeNowInMilliseconds = std::fmod(juce::Time::getMillisecondCounterHiRes(), 1000.0);
    deltaTimeInMilliseconds = timeNowInMilliseconds - timeThenInMilliseconds;

    double timeAtLastUpdate = timeNowInMilliseconds - deltaTimeInMilliseconds;

    int nextMessageIndex = cachedMidiSequence.getNextIndexAtTime(timeAtLastUpdate);
    bool reachedEndOfSequence = nextMessageIndex >= cachedMidiSequence.getNumEvents();

    int baseSampleNumber = 0;
    while (cachedMidiSequence.getEventTime(nextMessageIndex) < timeNowInMilliseconds && !reachedEndOfSequence)
    {
        auto currentMessagePointer = cachedMidiSequence.getEventPointer(nextMessageIndex);
        auto currentMessageTimeInMilliseconds = cachedMidiSequence.getEventTime(nextMessageIndex);
        auto currentMessage = currentMessagePointer->message;
        double sampleDurationInMilliseconds = 1000 / getSampleRate();
        double blockDurationInMilliseconds = getBlockSize() * sampleDurationInMilliseconds;

        //DBG(juce::String::formatted("before %f now %f next %f", timeThenInMilliseconds, timeNowInMilliseconds, timeNowInMilliseconds + blockDurationInMilliseconds));

        if (currentMessageTimeInMilliseconds <= timeNowInMilliseconds)
        {
            bool success = midiMessages.addEvent(currentMessage, baseSampleNumber++);
            if (success)
            {
                //DBG(juce::String("sending ") + currentMessage.getDescription() + juce::String(" at sample 0"));
            } else {
                //DBG(juce::String("failed to send") + currentMessage.getDescription() + juce::String(" at sample 0"));
            }
        } else if (currentMessageTimeInMilliseconds < timeNowInMilliseconds + blockDurationInMilliseconds) {
            double howFarInTheFutureTheTheSampleIsInMilliseconds = currentMessageTimeInMilliseconds - timeNowInMilliseconds;
            int sampleNumber = (int) howFarInTheFutureTheTheSampleIsInMilliseconds/sampleDurationInMilliseconds;
            bool success = midiMessages.addEvent(currentMessage, sampleNumber);
            if (success)
            {
                //DBG(juce::String("sending") + currentMessage.getDescription());
            } else {
                //DBG(juce::String("failed to send") + currentMessage.getDescription());
            }
        }

        if (nextMessageIndex == cachedMidiSequence.getNumEvents() - 1) break;

        nextMessageIndex++;
        reachedEndOfSequence = nextMessageIndex >= cachedMidiSequence.getNumEvents();
    }

    timeThenInMilliseconds = timeNowInMilliseconds;
    //DBG(juce::String(midiMessages));

    /*
    int noteNumber = (int) (time/100 + 50);
    auto messageOn = juce::MidiMessage::noteOn (0, noteNumber, (juce::uint8) 100);
    auto messageOff = juce::MidiMessage::noteOff (0, noteNumber, (juce::uint8) 100);
    midiMessages.addEvent(messageOn, 0);
    midiMessages.addEvent(messageOff, 0);
    */


    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool MicropitcherAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MicropitcherAudioProcessor::createEditor()
{
    return new MicropitcherAudioProcessorEditor (*this, valueTree);
}

//==============================================================================
void MicropitcherAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MicropitcherAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================

void MicropitcherAudioProcessor::valueTreePropertyChanged(juce::ValueTree& valueTree, const juce::Identifier& identifier)
{
    DBG("the plugin processor sees a property changing");
}

void MicropitcherAudioProcessor::valueTreeChildAdded(juce::ValueTree& parentTree, juce::ValueTree& childTree)
{
    if (childTree.getType() == TreeValues::graphIdentifier)
    {
    } else if (childTree.getType() == TreeValues::pathTreeIdentifier) {
        pathStringsChanged();
    }
}

std::vector<juce::String> MicropitcherAudioProcessor::readPathStringsFromValueTree()
{
    std::vector<juce::String> pathStrings = {};
    auto graphTree = valueTree.getChildWithName(TreeValues::graphIdentifier);
    for (int i = 0; i < graphTree.getNumChildren(); i++)
    {
        pathStrings.push_back(
            graphTree.getChild(i)
                .getProperty(TreeValues::pathStringIdentifier)
                .toString()
        );
    }
    return pathStrings;
}

void MicropitcherAudioProcessor::pathStringsChanged()
{
    DBG("The path strings were changed");
    std::vector<juce::String> pathStrings = readPathStringsFromValueTree();
    cachedMidiSequence = renderPathstringsToMidiSequence(pathStrings);
}

// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MicropitcherAudioProcessor();
}
