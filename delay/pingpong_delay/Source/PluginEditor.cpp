/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Pingpong_delayAudioProcessorEditor::Pingpong_delayAudioProcessorEditor (Pingpong_delayAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p),
      delayLengthLabel_("", "Delay(sec)"),
      feedbackLabel_("", "Feedback:"),
      dryMixLabel_("", "Dry Mix Level:"),
      wetMixLabel_("", "Delayed Mix Level:")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    addAndMakeVisible(&delayLengthSlider_);
    delayLengthSlider_.setSliderStyle(Slider::Rotary);
    delayLengthSlider_.addListener(this);
    delayLengthSlider_.setRange(0.01, 2.0, 0.01);

    addAndMakeVisible(&feedbackSlider_);
    feedbackSlider_.setSliderStyle(Slider::Rotary);
    feedbackSlider_.addListener(this);
    feedbackSlider_.setRange(0.00, 0.995, 0.005);

    addAndMakeVisible(&dryMixSlider_);
    dryMixSlider_.setSliderStyle(Slider::Rotary);
    dryMixSlider_.addListener(this);
    dryMixSlider_.setRange(0.00, 1.0, 0.01);

    addAndMakeVisible(&wetMixSlider_);
    wetMixSlider_.setSliderStyle(Slider::Rotary);
    wetMixSlider_.addListener(this);
    wetMixSlider_.setRange(0.00, 1.0, 0.01);

    delayLengthLabel_.attachToComponent(&delayLengthSlider_, false);
    feedbackLabel_.attachToComponent(&feedbackSlider_, false);
    dryMixLabel_.attachToComponent(&dryMixSlider_, false);
    wetMixLabel_.attachToComponent(&wetMixSlider_, false);
}

Pingpong_delayAudioProcessorEditor::~Pingpong_delayAudioProcessorEditor()
{
}

//==============================================================================
void Pingpong_delayAudioProcessorEditor::paint (Graphics& g)
{
    const int sliderWidth = 150;
    const int sliderHeight = 40;

    delayLengthSlider_.setBounds(20,20,sliderWidth,sliderHeight);
    feedbackSlider_.setBounds(200, 20, sliderWidth, sliderHeight);
    dryMixSlider_.setBounds(20, 80, sliderWidth, sliderHeight);
    wetMixSlider_.setBounds(200, 80, 150, 40);
}

void Pingpong_delayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
void Pingpong_delayAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    auto val = slider->getValue();

    if(&dryMixSlider_ == slider)
    {
        processor.setDryMix(val);
    }else if(&wetMixSlider_ == slider)
    {
        processor.setWetMix(val);
    }else if(&delayLengthSlider_ == slider)
    {
        processor.setDelayLength(val);
    }else if(&feedbackSlider_ == slider)
    {
        processor.setFeedback(val);
    }
}
