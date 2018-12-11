
#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"
#define NUMBER_OF_FILTERS 4
#define MAX_CHANNELS 2

#pragma once

class EqualizerProcessor {

public:


	EqualizerProcessor() {
		filterTypeH = PEAK;
		filterTypeL = PEAK;
	}



	void prepeareFilters(int numChannels, int sampleRate) {
		for (int n = 0; n < NUMBER_OF_FILTERS; ++n) {
			for (int i = 0; i < numChannels; ++i) {
				Filter * filter;
				filter = new Filter(sampleRate);
				filter->setFilterType(PEAK);
				allFilters[n][i] = filter;
			}
		}
		updateFilter(1000.0f, 1.0f, 0.0f, 0);
		updateFilter(4000.0f, 1.0f, 0.0f, 1);
		updateFilter(16000.0f, 1.0f, 0.0f, 2);
		updateFilter(19000.0f, 1.0f, 0.0f, 3);
		resetFiterH();
		resetFiterL();
	}

	void doProcessing(float* channelData, int numSamples, int channel) {
		for (int i = 0; i < NUMBER_OF_FILTERS; ++i) {
			allFilters[i][channel]->processSamples(channelData, numSamples);
		}
	}

	FILTER_TYPE getFilterType(int i) {
		return (allFilters[i][0])->getFilterType();
	}

	float getGain(int i) {
		return gains[i];
	}

	float getQuality(int i) {
		return qualities[i];
	}

	float getFrequency(int i) {
		return frequencies[i];
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
			(*xml).setAttribute("quality" + i, qualities[i]);
		}
		(*xml).setAttribute("ftL", (int)filterTypeL);  
		(*xml).setAttribute("ftH", (int)filterTypeH);
	}


	void restoreFromXml(ScopedPointer<XmlElement> xmlState) {

		for (int i = 0; i < NUMBER_OF_FILTERS; i++) { 

			gains[i] = xmlState->getDoubleAttribute("gain" + i, 0);
			qualities[i] = xmlState->getDoubleAttribute("quality" + i, 0);
			frequencies[i] = xmlState->getDoubleAttribute("freq" + i, 0);
		}

		filterTypeL = (FILTER_TYPE)(xmlState->getIntAttribute("ftL", 2));
		filterTypeH = (FILTER_TYPE)(xmlState->getIntAttribute("ftH", 1));
	}

	void updateFilter(float f, float q, float g, int i) {

		allFilters[i][0]->updateFilter(f, q, Decibels::decibelsToGain(g));
		allFilters[i][1]->updateFilter(f, q, Decibels::decibelsToGain(g));
		frequencies[i] = f;
		gains[i] = g;
		qualities[i] = q;
	}

private:

	Filter * allFilters[NUMBER_OF_FILTERS][MAX_CHANNELS];
	OwnedArray<OwnedArray<Filter>> ownedar; 
	
	FILTER_TYPE filterTypeL;
	FILTER_TYPE filterTypeH;
	float gains[NUMBER_OF_FILTERS];
	float qualities[NUMBER_OF_FILTERS];
	float frequencies[NUMBER_OF_FILTERS];



};