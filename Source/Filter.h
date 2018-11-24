


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
		//filter_type = PEAK;
		sample_rate = sampleRate;
		//updateFilter(20.0f, 1.0f, 1.0f); //SET DEF VALUES?
		//setCoefficients(IIRCoefficients::makeLowPass(sampleRate, 8000));
	}

	void setFilterType(FILTER_TYPE type) {
		filter_type = type;
	}

	FILTER_TYPE getFilterType() {
		return filter_type;
	}

	void prepare() {

	}

	void updateGain(float newVal) {
		gain = Decibels::gainToDecibels(newVal);
		//updateFilter(frequency, resonance, gain);
	}

	void updateResonance(float newVal) {
		resonance = newVal;
		//updateFilter(frequency, resonance, gain);
	}

	void updateFrequency(float newVal) {
		frequency = newVal;
		//updateFilter(frequency, resonance, gain);
	}

	void updateFilter(float f, float r, float g) { 
		frequency = f;
		gain = g;
		resonance = r;
		resetFilter();
	}

	void resetFilter() {

		if (filter_type == PEAK) {

			setCoefficients(IIRCoefficients::makePeakFilter(sample_rate, frequency, resonance, gain));

		}
		else if (filter_type == LP) {
			setCoefficients(IIRCoefficients::makeLowPass(sample_rate, frequency, resonance));

		}
		else if (filter_type == HP) {
			setCoefficients(IIRCoefficients::makeHighPass(sample_rate, frequency, resonance));
		}
		else if (filter_type == LS) {

			setCoefficients(IIRCoefficients::makeLowShelf(sample_rate, frequency, resonance, gain));
		}
		else if (filter_type == HS) {
			setCoefficients(IIRCoefficients::makeHighShelf(sample_rate, frequency, resonance, gain));
		}

		//setCoefficients(filter_coefficients);

	}




private:
	FILTER_TYPE filter_type;
	float frequency;
	float resonance;
	float gain;
	double sample_rate;
	IIRCoefficients filterCoefficients; 
};