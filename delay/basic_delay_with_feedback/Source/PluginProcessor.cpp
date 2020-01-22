/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Basic_delay_with_feedbackAudioProcessor::Basic_delay_with_feedbackAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

Basic_delay_with_feedbackAudioProcessor::~Basic_delay_with_feedbackAudioProcessor()
{
}

//==============================================================================
const String Basic_delay_with_feedbackAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Basic_delay_with_feedbackAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Basic_delay_with_feedbackAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Basic_delay_with_feedbackAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Basic_delay_with_feedbackAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Basic_delay_with_feedbackAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Basic_delay_with_feedbackAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Basic_delay_with_feedbackAudioProcessor::setCurrentProgram (int index)
{
}

const String Basic_delay_with_feedbackAudioProcessor::getProgramName (int index)
{
    return {};
}

void Basic_delay_with_feedbackAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Basic_delay_with_feedbackAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    delayBufferLength_ = static_cast<int>(2.0 * sampleRate);
    if(delayBufferLength_ < 1)
    {
        delayBufferLength_ = 1;
    }

    const int num_output_channel = 2;
    delayBuffer_.setSize(num_output_channel, delayBufferLength_);

    delayReadPosition_ = (int)(delayWritePosition_ - (delayLength_ * getSampleRate())
        + delayBufferLength_) % delayBufferLength_;
}

void Basic_delay_with_feedbackAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Basic_delay_with_feedbackAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void Basic_delay_with_feedbackAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    auto totalNumSamples = buffer.getNumSamples();

    size_t dpr = 0;
    size_t dpw = 0;

    for(int c = 0; c < totalNumInputChannels; ++c)
    {
        float* channelData = buffer.getWritePointer(c);
        float* delayData = delayBuffer_.getWritePointer(c);

        dpr = delayReadPosition_;
        dpw = delayWritePosition_;

        for(int i = 0; i < totalNumSamples; ++i)
        {
            const float in = channelData[i];
            float out = 0.0f;

            out = (dryMix_ * in + wetMix_ * delayData[dpr]);

            delayData[dpw] = in + (delayData[dpr] * feedback_);

            if(++dpr >= delayBufferLength_)
                dpr = 0;
            if(++dpw >= delayBufferLength_)
                dpw = 0;

            channelData[i] = out;
        }
    }

    delayReadPosition_ = dpr;
    delayWritePosition_ = dpw;

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
}

//==============================================================================
bool Basic_delay_with_feedbackAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Basic_delay_with_feedbackAudioProcessor::createEditor()
{
    return new Basic_delay_with_feedbackAudioProcessorEditor (*this);
}

//==============================================================================
void Basic_delay_with_feedbackAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Basic_delay_with_feedbackAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Basic_delay_with_feedbackAudioProcessor();
}
