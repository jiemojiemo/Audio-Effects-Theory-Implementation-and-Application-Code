/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
//==============================================================================
/**
*/
class Pingpong_delayAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    Pingpong_delayAudioProcessor();
    ~Pingpong_delayAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void setDelayLength(float DelayLength);
    void setDryMix(float DryMix);
    void setWetMix(float WetMix);
    void setFeedback(float Feedback);

private:
    void updateDelayBufferReadPointer();

private:
    float delayLength_ = 0.7;
    float dryMix_ = 1.0;
    float wetMix_ = 0.5;
    float feedback_ = 0.7;

    int delayBufferLength_ = 1;
    size_t delayReadPosition_ = 0;
    size_t delayWritePosition_ = 0;

    AudioBuffer<float> delayBuffer_;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Pingpong_delayAudioProcessor)
};
