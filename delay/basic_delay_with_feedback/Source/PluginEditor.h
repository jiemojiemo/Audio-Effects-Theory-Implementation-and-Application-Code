/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Basic_delay_with_feedbackAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    Basic_delay_with_feedbackAudioProcessorEditor (Basic_delay_with_feedbackAudioProcessor&);
    ~Basic_delay_with_feedbackAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Basic_delay_with_feedbackAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Basic_delay_with_feedbackAudioProcessorEditor)
};
