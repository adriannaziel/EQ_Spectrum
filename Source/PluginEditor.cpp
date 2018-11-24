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
	setSize(1000, 600);
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
	sliderFreqL.setRange(20.0f, 20000.0f, 1.0);
	sliderFreqL.setValue(processor.getFrequencyValue(0));
	sliderFreqL.setTextBoxStyle(Slider::TextBoxAbove, true, 100, 20);
	sliderFreqL.setTextValueSuffix("Hz");
	sliderFreqL.setTextBoxIsEditable(true);
	//sliderFreqL.setColour(Slider::thumbColourId, Colours::darkcyan);
	sliderFreqL.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqL.getValue(), sliderResL.getValue(), sliderGainL.getValue(), 0);
	};
	addAndMakeVisible(&sliderFreqL);

	sliderResL.setSliderStyle(Slider::Rotary);
	sliderResL.setRange(0.1f, 2.0f, 0.05);
	//sliderResL.setColour(Slider::thumbColourId, Colours::darkcyan);
	sliderResL.setValue(processor.getResonanceValue(0));
	sliderResL.setTextBoxStyle(Slider::TextBoxAbove, true, 100,20);
	sliderResL.setTextBoxIsEditable(true);

	sliderResL.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqL.getValue(), sliderResL.getValue(), sliderGainL.getValue(), 0);
	};
	addAndMakeVisible(&sliderResL);

	sliderGainL.setSliderStyle(Slider::Rotary);
	sliderGainL.setRange(-30.0f, 30.0f, 1.0f);
	sliderGainL.setTextValueSuffix("dB");
	//sliderGainL.setColour(Slider::thumbColourId, Colours::darkcyan);
	sliderGainL.setValue(processor.getGainValue(0));
	sliderGainL.setTextBoxStyle(Slider::TextBoxAbove, true, 80, 20);
	sliderGainL.setTextBoxIsEditable(true);

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
		processor.setNextFilterType(0);
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
	//sliderFreqLM.setColour(Slider::thumbColourId, Colours::darkgrey);
	sliderFreqLM.setTextBoxStyle(Slider::TextBoxAbove, true, 100, 20);
	sliderFreqLM.setTextValueSuffix("Hz");
	sliderFreqLM.setTextBoxIsEditable(true);

	sliderFreqLM.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqLM.getValue(), sliderResLM.getValue(), sliderGainLM.getValue(), 1);
	};
	addAndMakeVisible(&sliderFreqLM);


	sliderResLM.setSliderStyle(Slider::Rotary);
	//sliderResLM.setColour(Slider::thumbColourId, Colours::darkgrey);
	sliderResLM.setRange(0.1f, 2.0f, 0.05); //nie moze byc 0
	sliderResLM.setValue(processor.getResonanceValue(1));
	sliderResLM.setTextBoxStyle(Slider::TextBoxAbove, true, 80, 20);
	sliderResLM.setTextBoxIsEditable(true);

	sliderResLM.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqLM.getValue(), sliderResLM.getValue(), sliderGainLM.getValue(), 1);
	};
	addAndMakeVisible(&sliderResLM);

	sliderGainLM.setSliderStyle(Slider::Rotary);
	sliderGainLM.setRange(-30.0f, 30.0f, 1.0f); // nie moze byc od 0 - testy
	sliderGainLM.setValue(processor.getGainValue(1));
	//sliderGainLM.setColour(Slider::thumbColourId, Colours::darkgrey);
	sliderGainLM.setTextValueSuffix("dB");

	sliderGainLM.setTextBoxStyle(Slider::TextBoxAbove, true, 80, 20);
	sliderGainLM.setTextBoxIsEditable(true);

	sliderGainLM.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqLM.getValue(), sliderResLM.getValue(), sliderGainLM.getValue(), 1);
	};
	addAndMakeVisible(&sliderGainLM);

	//---HM-------------------------------------------------------------------------------------------------------------------

	sliderFreqHM.setSliderStyle(Slider::Rotary);
	sliderFreqHM.setRange(20.0f, 20000.0f, 1.0);
	sliderFreqHM.setTextValueSuffix("Hz");
	sliderFreqHM.setValue(processor.getFrequencyValue(2));
	sliderFreqHM.setTextBoxStyle(Slider::TextBoxAbove, true, 100, 20);
	sliderFreqHM.setTextBoxIsEditable(true);

	sliderFreqHM.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqHM.getValue(), sliderResHM.getValue(), sliderGainHM.getValue(), 2);
	};
	addAndMakeVisible(&sliderFreqHM);


	sliderResHM.setSliderStyle(Slider::Rotary);
	sliderResHM.setRange(0.1f, 2.0f, 0.05); //nie moze byc 0
	sliderResHM.setValue(processor.getResonanceValue(2));
	sliderResHM.setTextBoxStyle(Slider::TextBoxAbove, true, 80, 20);
	sliderResHM.setTextBoxIsEditable(true);

	sliderResHM.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqHM.getValue(), sliderResHM.getValue(), sliderGainHM.getValue(), 2);
	};
	addAndMakeVisible(&sliderResHM);


	sliderGainHM.setSliderStyle(Slider::Rotary);
	sliderGainHM.setRange(-30.0f, 30.0f, 1.0f);
	sliderGainHM.setValue(processor.getGainValue(2));
	sliderGainHM.setTextValueSuffix("dB");
	sliderGainHM.setTextBoxStyle(Slider::TextBoxAbove, true, 80, 20);
	sliderGainHM.setTextBoxIsEditable(true);

	sliderGainHM.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqHM.getValue(), sliderResHM.getValue(), sliderGainHM.getValue(), 2);
	};
	addAndMakeVisible(&sliderGainHM);

	//---H--------------------------------------------------------------------------------------------------------------------

	sliderFreqH.setSliderStyle(Slider::Rotary);
	sliderFreqH.setRange(20.0f, 20000.0f, 1.0);
	sliderFreqH.setTextValueSuffix("Hz");

	sliderFreqH.setValue(processor.getFrequencyValue(3));
	sliderFreqH.setTextBoxStyle(Slider::TextBoxAbove, true, 100, 20);
	sliderFreqH.setTextBoxIsEditable(true);

	sliderFreqH.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqH.getValue(), sliderResH.getValue(), sliderGainH.getValue(), 3);

	};
	addAndMakeVisible(&sliderFreqH);


	sliderResH.setSliderStyle(Slider::Rotary);
	sliderResH.setRange(0.1f, 2.0f, 0.05); //nie moze byc 0
	sliderResH.setValue(processor.getResonanceValue(3));
	sliderResH.setTextBoxStyle(Slider::TextBoxAbove, true, 80, 20);
	sliderResH.setTextBoxIsEditable(true);

	sliderResH.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqH.getValue(), sliderResH.getValue(), sliderGainH.getValue(), 3);
	};
	addAndMakeVisible(&sliderResH);

	sliderGainH.setSliderStyle(Slider::Rotary);
	sliderGainH.setTextValueSuffix("dB");
	sliderGainH.setRange(-30.0f, 30.0f, 1.0f); // nie moze byc od 0 - testy
	sliderGainH.setValue(processor.getGainValue(3));
	sliderGainH.setTextBoxStyle(Slider::TextBoxAbove, true, 80, 20);
	sliderGainH.setTextBoxIsEditable(true);

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
		processor.setNextFilterType(3);
		btnFilterTypeH.setButtonText(processor.getFilterTypeName(3));
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
	g.setColour(Colours::darkcyan);
	g.fillRect(0, 255, 100, 400);
	g.setColour(Colours::darkgrey);
	g.fillRect(100, 255,225,400);
	g.setColour(Colours::darkcyan);
	g.fillRect(325, 255, 225, 400);
	g.setColour(Colours::darkgrey);
	g.fillRect(550, 255, 225, 400);
	g.setColour(Colours::darkcyan);
	g.fillRect(775, 255, 225, 400);
	g.setOpacity(1.0f);

	g.setColour(Colours::white);
	g.setFont(17);
	g.drawText("PEAK", 420, 260, 50, 30, Justification::centred);
	g.drawText("PEAK", 640, 260, 50, 30,Justification::centred );
	g.setFont(26);
	g.drawText("F", 20, 330, 50, 30, Justification::centred);
	g.drawText("Q", 20, 430, 50, 30, Justification::centred);
	g.drawText("G", 20, 530, 50, 30, Justification::centred);


	sc.prepareToPaintSpectrum(processor.getFFTSize(), processor.getFFTData());


}

void Eq_spectrumAudioProcessorEditor::resized()
{
	buttonWindow.setBounds(0, 0, 100, 30);
	sc.setBounds(0, 20, 1000, 260);  // -


	btnFilterTypeL.setBounds(190, 260, 50, 30);
	sliderFreqL.setBounds(160, 300, 100, 100);
	sliderResL.setBounds(160, 400, 100, 100);
	sliderGainL.setBounds(160, 500, 100, 100);


	sliderFreqLM.setBounds(390, 300, 100, 100);
	sliderResLM.setBounds(390, 400, 100, 100);
	sliderGainLM.setBounds(390, 500, 100, 100);

	sliderFreqHM.setBounds(610, 300, 100, 100);
	sliderResHM.setBounds(610, 400, 100, 100);
	sliderGainHM.setBounds(610, 500, 100, 100);

	btnFilterTypeH.setBounds(870, 260, 50, 30);
	sliderFreqH.setBounds(830, 300, 100, 100);
	sliderResH.setBounds(830, 400, 100, 100);
	sliderGainH.setBounds(830, 500, 100, 100);

}

void Eq_spectrumAudioProcessorEditor::timerCallback()
{


	if (processor.isFFTBlockReady())
	{
		processor.processFFT();
		sc.prepareToPaintSpectrum(processor.getFFTSize(), processor.getFFTData());
		sc.repaint();
	}



}


