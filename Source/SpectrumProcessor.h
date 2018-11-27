
#include "../JuceLibraryCode/JuceHeader.h"
#pragma once

enum WINDOW_TYPE {
	BH,
	HANN,
	HAMMING,
	RECTANGULAR
};

class SpectrumProcessor {
public:

	SpectrumProcessor() : forwardFFT(fftOrder), window(fftSize, dsp::WindowingFunction<float>::hamming) {
		window_type = HAMMING;
	}

	enum 
	{
		fftOrder = 12,
		fftSize = 1 << fftOrder, 
	};



	float fftData[2 * fftSize];
	bool nextFFTBlockReady = false;



	float  fifo[fftSize];
	dsp::FFT forwardFFT;
	dsp::WindowingFunction<float> window;
	int fifoIndex = 0;
	WINDOW_TYPE window_type;


	void pushNextSampleIntoFifo(float sample) noexcept {
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

	void doProcessing()
	{
		window.multiplyWithWindowingTable(fftData, fftSize);
		forwardFFT.performFrequencyOnlyForwardTransform(fftData);
	}

	void setWindow(WINDOW_TYPE newWindowType) {
		if (newWindowType == HANN) {
			window.fillWindowingTables(fftSize, dsp::WindowingFunction<float>::hann);
			window_type = HANN;
		}
		else if (newWindowType == HAMMING) {
			window.fillWindowingTables(fftSize, dsp::WindowingFunction<float>::hamming);
			window_type = HAMMING;
		}

		else  if (newWindowType == RECTANGULAR) {
			window.fillWindowingTables(fftSize, dsp::WindowingFunction<float>::rectangular);
			window_type = RECTANGULAR;
		}
		else  if (newWindowType == BH) {
			window.fillWindowingTables(fftSize, dsp::WindowingFunction<float>::blackmanHarris);
			window_type = BH;
		}
	}

	void changeWindow()
	{
		if (window_type == BH) {
			setWindow(HANN);
		}
		else if (window_type == HANN) {
			setWindow(HAMMING);
		}

		else  if (window_type == HAMMING) {
			setWindow(RECTANGULAR);

		}
		else  if (window_type == RECTANGULAR) {
			setWindow(BH);
		}

	}

	String getWindowName()  
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

		else  if (window_type == RECTANGULAR) {
			return "rectangular";

		}

	}


	void saveToXml(XmlElement * xml) {
		(*xml).setAttribute("window", (int)window_type);
	}


	void restoreFromXml(ScopedPointer<XmlElement> xmlState) {
		setWindow((WINDOW_TYPE)(xmlState->getIntAttribute("window", 0)));

	}

private:




};