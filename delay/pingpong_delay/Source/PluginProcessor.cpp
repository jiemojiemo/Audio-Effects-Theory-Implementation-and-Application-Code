/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Pingpong_delayAudioProcessor::Pingpong_delayAudioProcessor()
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

Pingpong_delayAudioProcessor::~Pingpong_delayAudioProcessor()
{
}

//==============================================================================
const String Pingpong_delayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Pingpong_delayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Pingpong_delayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Pingpong_delayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Pingpong_delayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Pingpong_delayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Pingpong_delayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Pingpong_delayAudioProcessor::setCurrentProgram (int index)
{
}

const String Pingpong_delayAudioProcessor::getProgramName (int index)
{
    return {};
}

void Pingpong_delayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Pingpong_delayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    const int maxDelaySecond = 2;
    delayBufferLength_ = maxDelaySecond * sampleRate;

    const int numOutputChannel = 2;
    delayBuffer_.setSize(numOutputChannel, delayBufferLength_);

    updateDelayBufferReadPointer();
}

void Pingpong_delayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Pingpong_delayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void Pingpong_delayAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    auto totalNumSamples = buffer.getNumSamples();

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
    float* channelDataL = buffer.getWritePointer(0);
    float* channelDataR = buffer.getWritePointer(1);

    float* delayDataL = delayBuffer_.getWritePointer(0);
    float* delayDataR = delayBuffer_.getWritePointer(1);

    size_t dpr = delayReadPosition_;
    size_t dpw = delayWritePosition_;

    for(int i = 0; i < totalNumSamples; ++i)
    {
        const float inL = channelDataL[i];
        const float inR = channelDataR[i];
        float outL = (dryMix_ * inL) + (wetMix_ * delayDataL[dpr]);
        float outR = (dryMix_ * inR) + (wetMix_ * delayDataR[dpr]);

        delayDataL[dpw] = inL + (delayDataR[dpr] * feedback_);
        delayDataR[dpw] = inR + (delayDataL[dpr] * feedback_);

        if(++dpr >= delayBufferLength_)
            dpr = 0;
        if(++dpw >= delayBufferLength_)
            dpw = 0;

        channelDataL[i] = outL;
        channelDataR[i] = outR;
    }

    delayReadPosition_ = dpr;
    delayWritePosition_ = dpw;
}

//==============================================================================
bool Pingpong_delayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Pingpong_delayAudioProcessor::createEditor()
{
    return new Pingpong_delayAudioProcessorEditor (*this);
}

//==============================================================================
void Pingpong_delayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Pingpong_delayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}
void Pingpong_delayAudioProcessor::updateDelayBufferReadPointer()
{
     delayReadPosition_ = (int)(delayWritePosition_ - (delayLength_ * getSampleRate())
        + delayBufferLength_) % delayBufferLength_;
}
void Pingpong_delayAudioProcessor::setDelayLength(float DelayLength) {
    delayLength_ = DelayLength;

    updateDelayBufferReadPointer();
}
void Pingpong_delayAudioProcessor::setDryMix(float DryMix) {
    dryMix_ = DryMix;
}
void Pingpong_delayAudioProcessor::setWetMix(float WetMix) {
    wetMix_ = WetMix;
}
void Pingpong_delayAudioProcessor::setFeedback(float Feedback) {
    feedback_ = Feedback;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Pingpong_delayAudioProcessor();
}
