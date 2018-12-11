
#include "../JuceLibraryCode/JuceHeader.h"
#include "SpectrumComponent.h"

const int SpectrumComponent::frequenciesForLines[] = { 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000 };
const int SpectrumComponent::numberOfLines = 28;
//==============================================================================
SpectrumComponent::SpectrumComponent()
{
	setSize(600, 400);  
}

SpectrumComponent::~SpectrumComponent()
{
}

void SpectrumComponent::paint(Graphics& g)
{


	g.setColour(Colours::whitesmoke);
	for (int i = 0; i < numberOfLines; ++i)
	{
		const double proportion = frequenciesForLines[i] / (44100 / 2.0);
		int xPos = transformToLog(proportion) * (getWidth());
		g.drawVerticalLine(xPos, 10.0f, getHeight() - 50);
	}
	g.drawText("20Hz", 70, 195, 50, 50, Justification::centred);
	g.drawText("100Hz", 220, 195, 50, 50, Justification::centred);
	g.drawText("200Hz", 310, 195, 50, 50, Justification::centred);
	g.drawText("1kHz", 530, 195, 50, 50, Justification::centred);
	g.drawText("2kHz", 634, 195, 50, 50, Justification::centred);
	g.drawText("10kHz", 865, 195, 50, 50, Justification::centred);
	g.drawText("20kHz", 957, 195, 50, 50, Justification::centred);

	g.drawText("-70dB", 20, 180, 50, 50, Justification::centred);
	g.drawText("-30dB", 20, 82, 50, 50, Justification::centred);
	g.drawText("  10dB", 20, 9, 50, 50, Justification::top);

	g.setColour(Colours::darkcyan);
	paintSpectrum(g);
}

void SpectrumComponent::resized()
{
}

void SpectrumComponent::paintSpectrum(Graphics & g)
{

	float x = 0;
	float y = 0;

	float h = getHeight() - 50;

	float yLimited = 0.0f;
	float yMapped;

	if (x < 90) {
		x = 90;
	}

	yLimited = jlimit<float>(-60.0f, 20.0f, (1) * Decibels::gainToDecibels(spectrum_data[0]) - 20);
	yMapped = jmap<float>(yLimited, -60.0f, 20.0f, h, 10);
	y = yMapped;

	last_x = x;
	last_y = y;



	for (int i = 1; i < number_of_bins; i += 4)
	{
		x = transformToLog((float)i / number_of_bins) * (getWidth());

		yLimited = jlimit<float>(-60.0f, 20.0f, (1) * Decibels::gainToDecibels(spectrum_data[i]) - 20);
		yMapped = jmap<float>(yLimited, -60.0f, 20.0f, h, 10);
		y = yMapped;

		if (x < 90) {
			x = 90;
			y = last_y;
		}

		g.drawLine(last_x, last_y, x, y);
		last_x = x;
		last_y = y;
	}

}

void SpectrumComponent::prepareToPaintSpectrum(int numBins, float * data)
{
	number_of_bins = numBins;
	spectrum_data = data;
}

float SpectrumComponent::transformToLog(float valueToTransform)
{
	const float minimum = 1.0f;
	const float maximum = 1000.0f;
	return log10(minimum + ((maximum - minimum) * valueToTransform)) / log10(maximum);
}