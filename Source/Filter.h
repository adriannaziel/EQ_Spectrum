


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

	Filter(double sampleRate) {
		sampleRate = sampleRate;
	}

	void setFilterType(FILTER_TYPE type) {
		filterType = type;
	}

	FILTER_TYPE getFilterType() {
		return filterType;
	}

	

	void updateFilter(float f, float r, float g) { 
		frequency = f;
		gain = g;
		resonance = r;
		resetFilter();
	}

	void resetFilter() {

		if (filterType == PEAK) {

			filterCoefficients = IIRCoefficients::makePeakFilter(sampleRate, frequency, resonance, gain);

		}
		else if (filterType == LP) {
			filterCoefficients = IIRCoefficients::makeLowPass(sampleRate, frequency, resonance);

		}
		else if (filterType == HP) {
			filterCoefficients = IIRCoefficients::makeHighPass(sampleRate, frequency, resonance);
		}
		else if (filterType == LS) {

			filterCoefficients = IIRCoefficients::makeLowShelf(sampleRate, frequency, resonance, gain);
		}
		else if (filterType == HS) {
			filterCoefficients = IIRCoefficients::makeHighShelf(sampleRate, frequency, resonance, gain);
		}

		setCoefficients(filterCoefficients);

	}




private:
	FILTER_TYPE filterType;
	float frequency;
	float resonance;
	float gain;
	double sampleRate;
	IIRCoefficients filterCoefficients; 
};