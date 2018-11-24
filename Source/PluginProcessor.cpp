/*
==============================================================================

This file was auto-generated!

It contains the basic framework code for a JUCE plugin processor.

==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Eq_spectrumAudioProcessor::Eq_spectrumAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	)
#endif
{

}

Eq_spectrumAudioProcessor::~Eq_spectrumAudioProcessor()
{
}

//==============================================================================
const String Eq_spectrumAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool Eq_spectrumAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool Eq_spectrumAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool Eq_spectrumAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double Eq_spectrumAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int Eq_spectrumAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
				// so this should be at least 1, even if you're not really implementing programs.
}

int Eq_spectrumAudioProcessor::getCurrentProgram()
{
	return 0;
}

void Eq_spectrumAudioProcessor::setCurrentProgram(int index)
{
}

const String Eq_spectrumAudioProcessor::getProgramName(int index)
{
	return {};
}

void Eq_spectrumAudioProcessor::changeProgramName(int index, const String& newName)
{
}

//==============================================================================
void Eq_spectrumAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	equalizer_processor.prepeareFilters(getTotalNumInputChannels(), sampleRate);

}


String Eq_spectrumAudioProcessor::getFilterTypeName(int i)
{
	FILTER_TYPE filter_type;
	if (i == 0) {
		filter_type = equalizer_processor.filterTypeL;
	}
	else if (i == 3) {
		filter_type = equalizer_processor.filterTypeH;
	}

	if (filter_type == PEAK) {
		return "PEAK";
	}
	else if (filter_type == LP) {
		return "LP";
	}
	else if (filter_type == HP) {
		return "HP";
	}
	else if (filter_type == LS) {
		return "LS";
	}
	else if (filter_type == HS) {
		return "HS";
	}
	else {
		return "";
	}

}



void Eq_spectrumAudioProcessor::updateFilter(float f, float r, float g, int i) {
	equalizer_processor.updateFilter(f, r, g, i);
}

void Eq_spectrumAudioProcessor::setNextFilterType(int i)
{
	if (i == 0) {
		equalizer_processor.setNextFilterTypeLF();
	}
	else if (i == 3) {
		equalizer_processor.setNextFilterTypeHF();

	}
}

void Eq_spectrumAudioProcessor::setFilters()
{
	equalizer_processor.resetFiterH();
	equalizer_processor.resetFiterL();
}

float Eq_spectrumAudioProcessor::getGainValue(int i)
{
	return equalizer_processor.gains[i];
}

float Eq_spectrumAudioProcessor::getResonanceValue(int i)
{
	return equalizer_processor.resonances[i];
}

float Eq_spectrumAudioProcessor::getFrequencyValue(int i)
{
	return equalizer_processor.frequencies[i];
}


bool Eq_spectrumAudioProcessor::isFFTBlockReady()
{
	return spectrum_processor.nextFFTBlockReady;
}

void Eq_spectrumAudioProcessor::processFFT()
{
	spectrum_processor.doProcessing();
	spectrum_processor.nextFFTBlockReady = false;
}





void Eq_spectrumAudioProcessor::changeWindow()
{
	spectrum_processor.changeWindow();
}

String Eq_spectrumAudioProcessor::getWindowName()
{
	WINDOW_TYPE wt = spectrum_processor.window_type;
	if (wt == BH) {
		return "blackmann-harris";
	}
	else if (wt == HANN) {
		return "hann";

	}
	else if (wt == HAMMING) {
		return "hamming";
	}

	else  if (wt == RECTANGULAR) {
		return "rectangular";

	}

}

float * Eq_spectrumAudioProcessor::getFFTData()
{
	return spectrum_processor.fftData;
}

int Eq_spectrumAudioProcessor::getFFTSize()
{
	return spectrum_processor.fftSize / 2;
}

void Eq_spectrumAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Eq_spectrumAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	ignoreUnused(layouts);
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

void Eq_spectrumAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();
	const int numSamples = buffer.getNumSamples();

	setFilters();

	for (int channel = 0; channel < totalNumInputChannels; ++channel) {
		float* channelData = buffer.getWritePointer(channel);
		equalizer_processor.doProcessing(channelData, numSamples, channel);
	}


	for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
	{
		buffer.clear(i, 0, buffer.getNumSamples());
	}

	if (buffer.getNumChannels() > 0)
	{
		auto* channelData = buffer.getReadPointer(0);

		for (auto i = 0; i < buffer.getNumSamples(); ++i)
			spectrum_processor.pushNextSampleIntoFifo(channelData[i]);
	}

}






//==============================================================================
bool Eq_spectrumAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Eq_spectrumAudioProcessor::createEditor()
{
	return new Eq_spectrumAudioProcessorEditor(*this);
}

//==============================================================================
void Eq_spectrumAudioProcessor::getStateInformation(MemoryBlock& destData)
{
	XmlElement xml("PluginState");
	equalizer_processor.saveToXml(&xml);
	spectrum_processor.saveToXml(&xml);
	copyXmlToBinary(xml, destData);
}

void Eq_spectrumAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState != 0)
	{
		if (xmlState->hasTagName("PluginState"))
		{
			equalizer_processor.restoreFromXml(xmlState);
			spectrum_processor.restoreFromXml(xmlState);

		}
	}
}





//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new Eq_spectrumAudioProcessor();
}
