
#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"


#pragma once

class EqualizerProcessor {

public:
	Filter * allFilters[4][2];
	FILTER_TYPE filterTypeL;
	FILTER_TYPE filterTypeH;
	float gains[4];
	float resonances[4];
	float frequencies[4];


	EqualizerProcessor() {
		filterTypeH = PEAK;
		filterTypeL = PEAK;
	}


	void prepeareFilters(int numChannels, int sampleRate) {
		for (int n = 0; n < 4; ++n) {
			for (int i = 0; i < numChannels; ++i) {
				Filter* filter;
				filter = new Filter(sampleRate);
				filter->setFilterType(PEAK);
				allFilters[n][i] = filter;
			}
		}
		updateFilter(10000.0f, 1.0f, 0.0f, 0);
		updateFilter(10000.0f, 1.0f, 0.0f, 1);
		updateFilter(10000.0f, 1.0f, 0.0f, 2);
		updateFilter(10000.0f, 1.0f, 0.0f, 3);
	}

	void doProcessing(float* channelData, int numSamples, int channel) {
		for (int i = 0; i < 4; ++i) {
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
		for (int i = 0; i < 4; i++) { //jakis static z tego 4 np FILTERS_NUMBER
			(*xml).setAttribute("gain" + i, gains[i]);
			(*xml).setAttribute("freq" + i, frequencies[i]);
			(*xml).setAttribute("reson" + i, resonances[i]);
		}
		(*xml).setAttribute("ftL", (int)filterTypeL);  // moze zamoast zapisywañ string i bawic sie w name to inty 
		(*xml).setAttribute("ftH", (int)filterTypeH);
	}


	void restoreFromXml(ScopedPointer<XmlElement> xmlState) {

		for (int i = 0; i < 4; i++) { //jakis static z tego 4 np FILTERS_NUMBER

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