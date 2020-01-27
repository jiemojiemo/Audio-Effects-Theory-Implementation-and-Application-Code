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
class Pingpong_delayAudioProcessorEditor  : public AudioProcessorEditor,
                                            private Slider::Listener
{
public:
    Pingpong_delayAudioProcessorEditor (Pingpong_delayAudioProcessor&);
    ~Pingpong_delayAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
private:
    void sliderValueChanged(Slider *slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Pingpong_delayAudioProcessor& processor;

    Label delayLengthLabel_;
    Label feedbackLabel_;
    Label dryMixLabel_;
    Label wetMixLabel_;

    Slider delayLengthSlider_;
    Slider feedbackSlider_;
    Slider dryMixSlider_;
    Slider wetMixSlider_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Pingpong_delayAudioProcessorEditor)
};
