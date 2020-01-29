/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VibratoAudioProcessorEditor::VibratoAudioProcessorEditor (VibratoAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p),
      sweepWidthLabel_("", "Sweep Width (Sec.)"),
      frequencyLabel_("", "Frequency")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    addAndMakeVisible(&sweepWidthSlider_);
    sweepWidthSlider_.setSliderStyle(Slider::SliderStyle::Rotary);
    sweepWidthSlider_.setRange(0.001, 0.05, 0.0005);
    sweepWidthSlider_.addListener(this);

    addAndMakeVisible(&frequencySilder_);
    frequencySilder_.setSliderStyle(Slider::SliderStyle::Rotary);
    frequencySilder_.setRange(0.5, 5.0, 0.025);
    frequencySilder_.addListener(this);

    sweepWidthLabel_.attachToComponent(&sweepWidthSlider_, false);
    frequencyLabel_.attachToComponent(&frequencySilder_, false);
}

VibratoAudioProcessorEditor::~VibratoAudioProcessorEditor()
{
}

//==============================================================================
void VibratoAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::grey);
}

void VibratoAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    sweepWidthSlider_.setBounds(20, 20, 150, 40);
    frequencySilder_.setBounds(200, 20, 150, 40);
}
void VibratoAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    auto val = slider->getValue();

    if(&sweepWidthSlider_ == slider)
    {
        processor.setSweepWidth(val);
    }else if(&frequencySilder_ == slider)
    {
        processor.setFrequency(val);
    }
}
