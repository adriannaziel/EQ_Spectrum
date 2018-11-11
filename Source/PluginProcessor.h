/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"
//==============================================================================
/**
*/
enum WINDOW_TYPE {
	BH,
	HANN,
	HAMMING,
	RECTANGULAR,
	BLACKMANN
};

class Eq_spectrumAudioProcessor : public AudioProcessor
{
public:
	//==============================================================================
	Eq_spectrumAudioProcessor();
	~Eq_spectrumAudioProcessor();

	void pushNextSampleIntoFifo(float sample) noexcept;

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


	void doProcessing();
	void changeWindow();
	String getWindowName();

	enum // moze zamiast enuma to ustawic   a moze enum ok?
	{
		fftOrder = 12,
		fftSize = 1 << fftOrder, // 2^ ??
	};




	float fftData[2 * fftSize];
	bool nextFFTBlockReady = false;


	float getGainValue(int i);
	float getResonanceValue(int i);
	float getFrequencyValue(int i);
	String getFilterTypeName(int i);
	void updateFilter(float f, float r, float g, int i);
	void setNextFilterTypeLF();
	void setNextFilterTypeHF();




private:
	void resetFiterL();
	void resetFiterH();
	void setFilters();
	FILTER_TYPE getFilterTypeByName(String name);


	Filter* allFilters[4][2];
	FILTER_TYPE filterTypeL;
	FILTER_TYPE filterTypeH;
	float gains[4];
	float resonances[4];
	float frequencies[4];


	float  fifo[fftSize];
	dsp::FFT forwardFFT;
	dsp::WindowingFunction<float> window;
	int fifoIndex = 0;
	WINDOW_TYPE window_type;

	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Eq_spectrumAudioProcessor)
};
