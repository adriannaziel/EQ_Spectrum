
#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"
#define NUMBER_OF_FILTERS 4
#define MAX_CHANNELS 2

#pragma once

class EqualizerProcessor {

public:
	Filter * allFilters[NUMBER_OF_FILTERS][MAX_CHANNELS];
	FILTER_TYPE filterTypeL;
	FILTER_TYPE filterTypeH;
	float gains[NUMBER_OF_FILTERS];
	float resonances[NUMBER_OF_FILTERS];
	float frequencies[NUMBER_OF_FILTERS];


	EqualizerProcessor() {
		filterTypeH = LP;
		filterTypeL = HP;
	}


	void prepeareFilters(int numChannels, int sampleRate) {
		for (int n = 0; n < NUMBER_OF_FILTERS; ++n) {
			for (int i = 0; i < numChannels; ++i) {
				Filter* filter;
				filter = new Filter(sampleRate);
				filter->setFilterType(PEAK);
				allFilters[n][i] = filter;
			}
		}
		updateFilter(1000.0f, 1.0f, 0.0f, 0);
		updateFilter(4000.0f, 1.0f, 0.0f, 1);
		updateFilter(12000.0f, 1.0f, 0.0f, 2);
		updateFilter(16000.0f, 1.0f, 0.0f, 3);
		resetFiterH();
		resetFiterL();
	}

	void doProcessing(float* channelData, int numSamples, int channel) {
		for (int i = 0; i < NUMBER_OF_FILTERS; ++i) {
			allFilters[i][channel]->processSamples(channelData, numSamples);
		}
	}



	void resetFiterL()
	{
		allFilters[0][0]->setFilterType(filterTypeL);
		allFilters[0][1]->setFilterType(filterTypeL);
	}

	void resetFiterH()
	{
		allFilters[3][0]->setFilterType(filterTypeH);
		allFilters[3][1]->setFilterType(filterTypeH);
	}

	void setNextFilterTypeLF()
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



	void setNextFilterTypeHF()
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

	void saveToXml(XmlElement * xml) {
		for (int i = 0; i < NUMBER_OF_FILTERS; i++) { 
			(*xml).setAttribute("gain" + i, gains[i]);
			(*xml).setAttribute("freq" + i, frequencies[i]);
			(*xml).setAttribute("reson" + i, resonances[i]);
		}
		(*xml).setAttribute("ftL", (int)filterTypeL);  
		(*xml).setAttribute("ftH", (int)filterTypeH);
	}


	void restoreFromXml(ScopedPointer<XmlElement> xmlState) {

		for (int i = 0; i < NUMBER_OF_FILTERS; i++) { 

			gains[i] = xmlState->getDoubleAttribute("gain" + i, 0);
			resonances[i] = xmlState->getDoubleAttribute("reson" + i, 0);
			frequencies[i] = xmlState->getDoubleAttribute("freq" + i, 0);
		}

		filterTypeL = (FILTER_TYPE)(xmlState->getIntAttribute("ftL", 0));
		filterTypeH = (FILTER_TYPE)(xmlState->getIntAttribute("ftH", 0));
	}

	void updateFilter(float f, float r, float g, int i) {

		allFilters[i][0]->updateFilter(f, r, Decibels::decibelsToGain(g));
		allFilters[i][1]->updateFilter(f, r, Decibels::decibelsToGain(g));
		frequencies[i] = f;
		gains[i] = g;
		resonances[i] = r;
	}

private:




};