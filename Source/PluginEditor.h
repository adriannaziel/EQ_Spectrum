/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "SpectrumComponent.h"

//==============================================================================
/**
*/


class Eq_spectrumAudioProcessorEditor : public AudioProcessorEditor, public Timer
{

public:
	Eq_spectrumAudioProcessorEditor(Eq_spectrumAudioProcessor&);
	~Eq_spectrumAudioProcessorEditor();

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;
	void timerCallback() override;

private:
	TextButton buttonWindow;
	SpectrumComponent sc;


	Eq_spectrumAudioProcessor& processor;


	Slider sliderFreqL;
	Slider sliderQualityL;
	Slider sliderGainL;
	TextButton btnFilterTypeL;


	Slider sliderFreqLM;
	Slider sliderQualityLM;
	Slider sliderGainLM;

	Slider sliderFreqHM;
	Slider sliderQualityHM;
	Slider sliderGainHM;

	Slider sliderFreqH;
	Slider sliderQualityH;
	Slider sliderGainH;
	TextButton btnFilterTypeH;


	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Eq_spectrumAudioProcessorEditor)
};
