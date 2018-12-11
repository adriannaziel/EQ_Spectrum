/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "EqualizerProcesor.h"
#include "SpectrumProcessor.h"
//==============================================================================
/**
*/
class Eq_spectrumAudioProcessor : public AudioProcessor
{
public:
	//==============================================================================
	Eq_spectrumAudioProcessor();
	~Eq_spectrumAudioProcessor();


	//==============================================================================
	void prepareToPlay(double sampleRate, int samplesPerBlock) override;
	void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
	bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

	void processBlock(AudioBuffer<float>&, MidiBuffer&) override;

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
	void setCurrentProgram(int index) override;
	const String getProgramName(int index) override;
	void changeProgramName(int index, const String& newName) override;

	//==============================================================================
	void getStateInformation(MemoryBlock& destData) override;
	void setStateInformation(const void* data, int sizeInBytes) override;


	float getGainValue(int i);
	float getQualityValue(int i);
	float getFrequencyValue(int i);
	String getFilterTypeName(int i);
	void updateFilter(float f, float q, float g, int i);
	void setNextFilterType(int i);
	void setFilters();

	bool isFFTBlockReady();
	void processFFT();
	void changeWindow(); 
	String getWindowName();
	float * getFFTData();
	int getFFTSize();


private:
	EqualizerProcessor equalizer_processor;
	SpectrumProcessor spectrum_processor;



	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Eq_spectrumAudioProcessor)
};
