/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Basic_delay_with_feedbackAudioProcessorEditor::Basic_delay_with_feedbackAudioProcessorEditor (Basic_delay_with_feedbackAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p),
      delayLengthLabel_("", "Delay(sec)"),
      feedbackLabel_("", "Feedback:"),
      dryMixLabel_("", "Dry Mix Level:"),
      wetMixLabel_("", "Delayed Mix Level:")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (350, 150);

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

Basic_delay_with_feedbackAudioProcessorEditor::~Basic_delay_with_feedbackAudioProcessorEditor()
{
}

//==============================================================================
void Basic_delay_with_feedbackAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
}

void Basic_delay_with_feedbackAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    const int sliderWidth = 150;
    const int sliderHeight = 40;

    delayLengthSlider_.setBounds(20,20,sliderWidth,sliderHeight);
    feedbackSlider_.setBounds(200, 20, sliderWidth, sliderHeight);
    dryMixSlider_.setBounds(20, 80, sliderWidth, sliderHeight);
    wetMixSlider_.setBounds(200, 80, 150, 40);
}
void Basic_delay_with_feedbackAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    float val = slider->getValue();

    if(slider == &delayLengthSlider_)
    {
        processor.setDelayLength(val);
    }
    else if(slider == &feedbackSlider_)
    {
        processor.setFeedback(val);
    }
    else if(slider == &dryMixSlider_)
    {
        processor.setDryMix(val);
    }
    else if(slider == &wetMixSlider_)
    {
        processor.setWetMix(val);
    }
}
