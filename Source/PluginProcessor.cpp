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
	), forwardFFT(fftOrder), window(fftSize, dsp::WindowingFunction<float>::hamming)
#endif
{
	window_type = HAMMING;
	filterTypeH = PEAK;
	filterTypeL = PEAK;
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
	for (int n = 0; n < 4; ++n) {
		for (int i = 0; i < getTotalNumInputChannels(); ++i) {
			Filter* filter;
			filter = new Filter(sampleRate);
			filter->setFilterType(PEAK);
			allFilters[n][i] = filter;
		}
	}
	updateFilter(20.0f, 0.5f, 0.0f, 0);
	updateFilter(1000.0f, 0.5f, 0.0f, 1);
	updateFilter(10000.0f, 0.5f, 0.0f, 2);
	updateFilter(10000.0f, 0.5f, 0.0f, 3);
}

void Eq_spectrumAudioProcessor::resetFiterL()
{
	allFilters[0][0]->setFilterType(filterTypeL);
	allFilters[0][1]->setFilterType(filterTypeL);
}

void Eq_spectrumAudioProcessor::resetFiterH()
{
	allFilters[3][0]->setFilterType(filterTypeH);
	allFilters[3][1]->setFilterType(filterTypeH);
}


String Eq_spectrumAudioProcessor::getFilterTypeName(int i)
{
	FILTER_TYPE filter_type;
	if (i == 0) {
		filter_type = filterTypeL;
	}
	else if (i == 3) {
		filter_type = filterTypeH;
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

FILTER_TYPE Eq_spectrumAudioProcessor::getFilterTypeByName(String name)
{
	if (name == "PEAK") {
		return PEAK;
	}
	else if (name == "LP") {
		return LP;
	}
	else if (name == "HP") {
		return HP;
	}
	else if (name == "LS") {
		return LS;
	}
	else if (name == "HS") {
		return HS;
	}
	else {
		return PEAK; //???????????
	}
	return PEAK;
}

void Eq_spectrumAudioProcessor::setNextFilterTypeLF()
{
	if (filterTypeL == PEAK) {
		filterTypeL = HP;
		resetFiterL();
	}
	else if (filterTypeL == HP) {
		filterTypeL = LS;
		resetFiterL();
	}
	else if (filterTypeL == LS) {
		filterTypeL = PEAK;
		resetFiterL();
	}
}

void Eq_spectrumAudioProcessor::setNextFilterTypeHF()
{
	if (filterTypeH == PEAK) {
		filterTypeH = LP;
		resetFiterH();
	}
	else if (filterTypeH == LP) {
		filterTypeH = HS;
		resetFiterH();
	}
	else if (filterTypeH == HS) {
		filterTypeH = PEAK;
		resetFiterH();
	}
}



void Eq_spectrumAudioProcessor::updateFilter(float f, float r, float g, int i) {

	allFilters[i][0]->updateFilter(f, r, Decibels::decibelsToGain(g));
	allFilters[i][1]->updateFilter(f, r, Decibels::decibelsToGain(g));
	frequencies[i] = f;
	gains[i] = g;
	resonances[i] = r;
}

void Eq_spectrumAudioProcessor::setFilters()
{
	resetFiterH();
	resetFiterL();
}

float Eq_spectrumAudioProcessor::getGainValue(int i)
{
	return gains[i];
}

float Eq_spectrumAudioProcessor::getResonanceValue(int i)
{
	return resonances[i];
}

float Eq_spectrumAudioProcessor::getFrequencyValue(int i)
{
	return frequencies[i];
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
		for (int i = 0; i < 4; ++i) {
			allFilters[i][channel]->processSamples(channelData, numSamples);
		}
	}

	for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
	{
		buffer.clear(i, 0, buffer.getNumSamples());
	}


	if (buffer.getNumChannels() > 0)
	{
		auto* channelData = buffer.getReadPointer(0);

		for (auto i = 0; i < buffer.getNumSamples(); ++i)
			pushNextSampleIntoFifo(channelData[i]);
	}
}


void Eq_spectrumAudioProcessor::pushNextSampleIntoFifo(float sample) noexcept
{

	if (fifoIndex == fftSize)
	{
		if (!nextFFTBlockReady)
		{
			zeromem(fftData, sizeof(fftData));
			memcpy(fftData, fifo, sizeof(fifo));
			nextFFTBlockReady = true;
		}

		fifoIndex = 0;
	}

	fifo[fifoIndex++] = sample;
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
	XmlElement xml("PluginStateEQSP");

	for (int i = 0; i < 4; i++) { //jakis static z tego 4 np FILTERS_NUMBER
		xml.setAttribute("gain" + i, gains[i]);
		xml.setAttribute("freq" + i, frequencies[i]);
		xml.setAttribute("reson" + i, resonances[i]);
	}
	xml.setAttribute("ftL", getFilterTypeName(0));
	xml.setAttribute("ftH", getFilterTypeName(3));

	copyXmlToBinary(xml, destData);
}

void Eq_spectrumAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState != 0)
	{
		if (xmlState->hasTagName("PluginStateEQSP"))
		{
			for (int i = 0; i < 4; i++) { //jakis static z tego 4 np FILTERS_NUMBER
				gains[i] = xmlState->getDoubleAttribute("gain" + i, 0);
				resonances[i] = xmlState->getDoubleAttribute("reson" + i, 0);
				frequencies[i] = xmlState->getDoubleAttribute("freq" + i, 0);
			}
			filterTypeL = getFilterTypeByName(xmlState->getStringAttribute("ftL", "PEAK"));
			filterTypeH = getFilterTypeByName(xmlState->getStringAttribute("ftH", "PEAK"));
		}
	}
}

void Eq_spectrumAudioProcessor::doProcessing()
{

	window.multiplyWithWindowingTable(fftData, fftSize);
	forwardFFT.performFrequencyOnlyForwardTransform(fftData);
}



void Eq_spectrumAudioProcessor::changeWindow()
{
	if (window_type == BH) {
		window.fillWindowingTables(fftSize, dsp::WindowingFunction<float>::hann);
		window_type = HANN;
	}
	else if (window_type == HANN) {
		window.fillWindowingTables(fftSize, dsp::WindowingFunction<float>::hamming);
		window_type = HAMMING;
	}

	else  if (window_type == HAMMING) {
		window.fillWindowingTables(fftSize, dsp::WindowingFunction<float>::rectangular);
		window_type = RECTANGULAR;
	}
	else  if (window_type == RECTANGULAR) {
		window.fillWindowingTables(fftSize, dsp::WindowingFunction<float>::blackman);
		window_type = BLACKMANN;
	}
	else  if (window_type == BLACKMANN) {
		window.fillWindowingTables(fftSize, dsp::WindowingFunction<float>::blackmanHarris);
		window_type = BH;
	}

}

String Eq_spectrumAudioProcessor::getWindowName()
{
	if (window_type == BH) {
		return "blackmann-harris";
	}
	else if (window_type == HANN) {
		return "hann";

	}
	else if (window_type == HAMMING) {
		return "hamming";
	}
	else  if (window_type == BLACKMANN) {
		return "blackmann";
	}
	else  if (window_type == RECTANGULAR) {
		return "rectangular";

	}

}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new Eq_spectrumAudioProcessor();
}
