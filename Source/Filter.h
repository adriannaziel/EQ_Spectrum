


#pragma once
#include "../JuceLibraryCode/JuceHeader.h"




enum FILTER_TYPE {
	PEAK,
	LP,
	HP,
	LS,
	HS
};

class Filter : public IIRFilter
{
public:

	Filter(double sampleRateParam) {
		sampleRate = sampleRateParam;
	}

	void setFilterType(FILTER_TYPE type) {
		filterType = type;
	}

	FILTER_TYPE getFilterType() {
		return filterType;
	}

	

	void updateFilter(float f, float q, float g) { 
		frequency = f;
		gain = g;
		quality = q;
		resetFilter();
	}

	void resetFilter() {

		if (filterType == PEAK) {

			filterCoefficients = IIRCoefficients::makePeakFilter(sampleRate, frequency, quality, gain);

		}
		else if (filterType == LP) {
			filterCoefficients = IIRCoefficients::makeLowPass(sampleRate, frequency, quality);

		}
		else if (filterType == HP) {
			filterCoefficients = IIRCoefficients::makeHighPass(sampleRate, frequency, quality);
		}
		else if (filterType == LS) {

			filterCoefficients = IIRCoefficients::makeLowShelf(sampleRate, frequency, quality, gain);
		}
		else if (filterType == HS) {
			filterCoefficients = IIRCoefficients::makeHighShelf(sampleRate, frequency, quality, gain);
		}

		setCoefficients(filterCoefficients);

	}




private:
	FILTER_TYPE filterType;
	float frequency;
	float quality;
	float gain;
	double sampleRate;
	IIRCoefficients filterCoefficients; 
};