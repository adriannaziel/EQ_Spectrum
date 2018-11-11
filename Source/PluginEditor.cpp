/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
Eq_spectrumAudioProcessorEditor::Eq_spectrumAudioProcessorEditor(Eq_spectrumAudioProcessor& p)
	: AudioProcessorEditor(&p), processor(p)
{
	setOpaque(true);
	startTimerHz(30);
	setSize(1000, 800);
	setResizable(true, true);

	buttonWindow.setButtonText(processor.getWindowName());
	buttonWindow.onClick = [this] {
		processor.changeWindow();
		buttonWindow.setButtonText(processor.getWindowName());
	};
	addAndMakeVisible(buttonWindow);

	addAndMakeVisible(sc);



	//---L-------------------------------------------------------------------------------------------------------------------
	sliderFreqL.setSliderStyle(Slider::Rotary);
	sliderFreqL.NoTextBox;
	sliderFreqL.setRange(20.0f, 20000.0f, 1.0);
	sliderFreqL.setValue(processor.getFrequencyValue(0));
	sliderFreqL.setTextBoxStyle(Slider::TextBoxAbove, true, 100, 40);
	sliderFreqL.setDoubleClickReturnValue(true, 20.0f);
	sliderFreqL.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqL.getValue(), sliderResL.getValue(), sliderGainL.getValue(), 0);
	};
	addAndMakeVisible(&sliderFreqL);

	sliderResL.setSliderStyle(Slider::Rotary);
	sliderResL.setRange(0.1f, 2.0f, 0.05);
	sliderResL.setValue(processor.getResonanceValue(0));
	sliderResL.setTextBoxStyle(Slider::TextBoxAbove, true, 80, 40);
	sliderResL.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqL.getValue(), sliderResL.getValue(), sliderGainL.getValue(), 0);
	};
	addAndMakeVisible(&sliderResL);

	sliderGainL.setSliderStyle(Slider::Rotary);
	sliderGainL.setRange(-20.0f, 20.0f, 1.0f);
	sliderGainL.setValue(processor.getGainValue(0));
	sliderGainL.setTextBoxStyle(Slider::TextBoxAbove, true, 80, 40);
	sliderGainL.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqL.getValue(), sliderResL.getValue(), sliderGainL.getValue(), 0);
	};
	addAndMakeVisible(&sliderGainL);

	btnFilterTypeL.setButtonText(processor.getFilterTypeName(0));
	//prepareButton(&btnFilterTypeL, 0);

	if (btnFilterTypeL.getButtonText() == "HP") {
		sliderGainL.setVisible(false);
	}
	else {
		sliderGainL.setVisible(true);
	}

	btnFilterTypeL.onClick = [this]
	{
		processor.setNextFilterTypeLF();
		btnFilterTypeL.setButtonText(processor.getFilterTypeName(0));// disable gain 

		if (btnFilterTypeL.getButtonText() == "HP") {
			sliderGainL.setVisible(false);
		}
		else {
			sliderGainL.setVisible(true);

		}	//	prepareButton(&btnFilterTypeL, 0);
		processor.updateFilter(sliderFreqL.getValue(), sliderResL.getValue(), sliderGainL.getValue(), 0); // CHANGE THE VALUES!!!!
	};

	addAndMakeVisible(&btnFilterTypeL);


	//---LM-------------------------------------------------------------------------------------------------------------------

	sliderFreqLM.setSliderStyle(Slider::Rotary);
	sliderFreqLM.setRange(20.0f, 20000.0f, 1.0);
	sliderFreqLM.setValue(processor.getFrequencyValue(1));
	sliderFreqLM.setDoubleClickReturnValue(true, 200.0f);
	sliderFreqLM.setTextBoxStyle(Slider::TextBoxAbove, true, 100, 40);
	sliderFreqLM.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqLM.getValue(), sliderResLM.getValue(), sliderGainLM.getValue(), 1);
	};
	addAndMakeVisible(&sliderFreqLM);


	sliderResLM.setSliderStyle(Slider::Rotary);
	sliderResLM.setRange(0.1f, 2.0f, 0.05); //nie moze byc 0
	sliderResLM.setValue(processor.getResonanceValue(1));
	sliderResLM.setTextBoxStyle(Slider::TextBoxAbove, true, 80, 40);
	sliderResLM.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqLM.getValue(), sliderResLM.getValue(), sliderGainLM.getValue(), 1);
	};
	addAndMakeVisible(&sliderResLM);

	sliderGainLM.setSliderStyle(Slider::Rotary);
	sliderGainLM.setRange(-20.0f, 20.0f, 1.0f); // nie moze byc od 0 - testy
	sliderGainLM.setValue(processor.getGainValue(1));
	sliderGainLM.setTextBoxStyle(Slider::TextBoxAbove, true, 80, 40);
	sliderGainLM.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqLM.getValue(), sliderResLM.getValue(), sliderGainLM.getValue(), 1);
	};
	addAndMakeVisible(&sliderGainLM);

	//---HM-------------------------------------------------------------------------------------------------------------------

	sliderFreqHM.setSliderStyle(Slider::Rotary);
	sliderFreqHM.setRange(20.0f, 20000.0f, 1.0);
	sliderFreqHM.setValue(processor.getFrequencyValue(2));
	sliderFreqHM.setTextBoxStyle(Slider::TextBoxAbove, true, 100, 40);
	sliderFreqHM.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqHM.getValue(), sliderResHM.getValue(), sliderGainHM.getValue(), 2);
	};
	addAndMakeVisible(&sliderFreqHM);


	sliderResHM.setSliderStyle(Slider::Rotary);
	sliderResHM.setRange(0.1f, 2.0f, 0.05); //nie moze byc 0
	sliderResHM.setValue(processor.getResonanceValue(2));
	sliderResHM.setTextBoxStyle(Slider::TextBoxAbove, true, 80, 40);
	sliderResHM.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqHM.getValue(), sliderResHM.getValue(), sliderGainHM.getValue(), 2);
	};
	addAndMakeVisible(&sliderResHM);


	sliderGainHM.setSliderStyle(Slider::Rotary);
	sliderGainHM.setRange(-20.0f, 20.0f, 1.0f);
	sliderGainHM.setValue(processor.getGainValue(2));
	sliderGainHM.setTextBoxStyle(Slider::TextBoxAbove, true, 80, 40);
	sliderGainHM.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqHM.getValue(), sliderResHM.getValue(), sliderGainHM.getValue(), 2);
	};
	addAndMakeVisible(&sliderGainHM);

	//---H--------------------------------------------------------------------------------------------------------------------

	sliderFreqH.setSliderStyle(Slider::Rotary);
	sliderFreqH.setRange(20.0f, 20000.0f, 1.0);
	sliderFreqH.setValue(processor.getFrequencyValue(3));
	sliderFreqH.setTextBoxStyle(Slider::TextBoxAbove, true, 100, 40);
	sliderFreqH.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqH.getValue(), sliderResH.getValue(), sliderGainH.getValue(), 3);

	};
	addAndMakeVisible(&sliderFreqH);


	sliderResH.setSliderStyle(Slider::Rotary);
	sliderResH.setRange(0.1f, 2.0f, 0.05); //nie moze byc 0
	sliderResH.setValue(processor.getResonanceValue(3));
	sliderResH.setTextBoxStyle(Slider::TextBoxAbove, true, 80, 40);
	sliderResH.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqH.getValue(), sliderResH.getValue(), sliderGainH.getValue(), 3);
	};
	addAndMakeVisible(&sliderResH);

	sliderGainH.setSliderStyle(Slider::Rotary);
	sliderGainH.setRange(-20.0f, 20.0f, 1.0f); // nie moze byc od 0 - testy
	sliderGainH.setValue(processor.getGainValue(3));
	sliderGainH.setTextBoxStyle(Slider::TextBoxAbove, true, 80, 40);
	sliderGainH.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqH.getValue(), sliderResH.getValue(), sliderGainH.getValue(), 3);
	};
	addAndMakeVisible(&sliderGainH);

	btnFilterTypeH.setButtonText(processor.getFilterTypeName(3));
	//prepareButton(&btnFilterTypeH, 3);

	if (btnFilterTypeH.getButtonText() == "LP") {
		sliderGainH.setVisible(false);
	}
	else {
		sliderGainH.setVisible(true);
	}
	btnFilterTypeH.onClick = [this]
	{
		processor.setNextFilterTypeHF();
		//prepareButton(&btnFilterTypeH, 3);
		if (btnFilterTypeH.getButtonText() == "LP") {
			sliderGainH.setVisible(false);
		}
		else {
			sliderGainH.setVisible(true);
		}
		//btnFilterTypeH.setButtonText(processor.getFilterTypeName(3));
		processor.updateFilter(sliderFreqH.getValue(), sliderResH.getValue(), sliderGainH.getValue(), 3); // CHANGE THE VALUES!!!!
	};
	addAndMakeVisible(&btnFilterTypeH);

}


Eq_spectrumAudioProcessorEditor::~Eq_spectrumAudioProcessorEditor()
{
}

//==============================================================================
void Eq_spectrumAudioProcessorEditor::paint(Graphics& g)
{
	g.fillAll(Colours::black);
	g.setOpacity(1.0f);
	sc.prepareToPaintSpectrum(processor.fftSize / 2, processor.fftData);
}

void Eq_spectrumAudioProcessorEditor::resized()
{
	buttonWindow.setBounds(20, 20, 100, 20);
	sc.setBounds(0, 50, 1000, 300);

	int h_base = 300;

	btnFilterTypeL.setBounds(40, h_base + 40, 50, 30);
	sliderFreqL.setBounds(10, h_base + 80, 120, 120);
	sliderResL.setBounds(10, h_base + 210, 120, 120);
	sliderGainL.setBounds(10, h_base + 350, 120, 120);


	//sliderFreqLM.setBounds(210, 80, 120, 120);
	//sliderResLM.setBounds(210, 210, 120, 120);
	//sliderGainLM.setBounds(210, 350, 120, 120);

	//sliderFreqHM.setBounds(390, 80, 120, 120);
	//sliderResHM.setBounds(390, 210, 120, 120);
	//sliderGainHM.setBounds(390, 350, 120, 120);

	//btnFilterTypeH.setBounds(590, 40, 50, 30);
	//sliderFreqH.setBounds(560, 80, 120, 120);
	//sliderResH.setBounds(560, 210, 120, 120);
	//sliderGainH.setBounds(560, 350, 120, 120);
}

void Eq_spectrumAudioProcessorEditor::timerCallback()
{


	if (processor.nextFFTBlockReady == true)
	{
		processor.doProcessing();
		processor.nextFFTBlockReady = false;
		sc.prepareToPaintSpectrum(processor.fftSize / 2, processor.fftData);
		sc.repaint();
	}



}


