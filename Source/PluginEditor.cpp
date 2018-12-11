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
	sliderFreqL.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqL.getValue(), sliderQualityL.getValue(), sliderGainL.getValue(), 0);
	};
	addAndMakeVisible(&sliderFreqL);

	sliderQualityL.setSliderStyle(Slider::Rotary);
	sliderQualityL.setRange(0.1f, 2.0f, 0.05);
	sliderQualityL.setValue(processor.getQualityValue(0));
	sliderQualityL.setTextBoxStyle(Slider::TextBoxAbove, true, 100,20);
	sliderQualityL.setTextBoxIsEditable(true);

	sliderQualityL.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqL.getValue(), sliderQualityL.getValue(), sliderGainL.getValue(), 0);
	};
	addAndMakeVisible(&sliderQualityL);

	sliderGainL.setSliderStyle(Slider::Rotary);
	sliderGainL.setRange(-30.0f, 30.0f, 1.0f);
	sliderGainL.setTextValueSuffix("dB");
	sliderGainL.setValue(processor.getGainValue(0));
	sliderGainL.setTextBoxStyle(Slider::TextBoxAbove, true, 80, 20);
	sliderGainL.setTextBoxIsEditable(true);

	sliderGainL.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqL.getValue(), sliderQualityL.getValue(), sliderGainL.getValue(), 0);
	};
	addAndMakeVisible(&sliderGainL);

	btnFilterTypeL.setButtonText(processor.getFilterTypeName(0));

	if (btnFilterTypeL.getButtonText() == "HP") {
		sliderGainL.setVisible(false);
	}
	else {
		sliderGainL.setVisible(true);
	}

	btnFilterTypeL.onClick = [this]
	{
		processor.setNextFilterType(0);
		btnFilterTypeL.setButtonText(processor.getFilterTypeName(0));

		if (btnFilterTypeL.getButtonText() == "HP") {
			sliderGainL.setVisible(false);
		}
		else {
			sliderGainL.setVisible(true);

		}	
		processor.updateFilter(sliderFreqL.getValue(), sliderQualityL.getValue(), sliderGainL.getValue(), 0); 
	};

	addAndMakeVisible(&btnFilterTypeL);


	//---LM-------------------------------------------------------------------------------------------------------------------

	sliderFreqLM.setSliderStyle(Slider::Rotary);
	sliderFreqLM.setRange(20.0f, 20000.0f, 1.0);
	sliderFreqLM.setValue(processor.getFrequencyValue(1));
	sliderFreqLM.setDoubleClickReturnValue(true, 200.0f);
	sliderFreqLM.setTextBoxStyle(Slider::TextBoxAbove, true, 100, 20);
	sliderFreqLM.setTextValueSuffix("Hz");
	sliderFreqLM.setTextBoxIsEditable(true);

	sliderFreqLM.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqLM.getValue(), sliderQualityLM.getValue(), sliderGainLM.getValue(), 1);
	};
	addAndMakeVisible(&sliderFreqLM);


	sliderQualityLM.setSliderStyle(Slider::Rotary);
	sliderQualityLM.setRange(0.1f, 2.0f, 0.05); 
	sliderQualityLM.setValue(processor.getQualityValue(1));
	sliderQualityLM.setTextBoxStyle(Slider::TextBoxAbove, true, 80, 20);
	sliderQualityLM.setTextBoxIsEditable(true);

	sliderQualityLM.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqLM.getValue(), sliderQualityLM.getValue(), sliderGainLM.getValue(), 1);
	};
	addAndMakeVisible(&sliderQualityLM);

	sliderGainLM.setSliderStyle(Slider::Rotary);
	sliderGainLM.setRange(-30.0f, 30.0f, 1.0f); 
	sliderGainLM.setValue(processor.getGainValue(1));
	sliderGainLM.setTextValueSuffix("dB");

	sliderGainLM.setTextBoxStyle(Slider::TextBoxAbove, true, 80, 20);
	sliderGainLM.setTextBoxIsEditable(true);

	sliderGainLM.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqLM.getValue(), sliderQualityLM.getValue(), sliderGainLM.getValue(), 1);
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
		processor.updateFilter(sliderFreqHM.getValue(), sliderQualityHM.getValue(), sliderGainHM.getValue(), 2);
	};
	addAndMakeVisible(&sliderFreqHM);


	sliderQualityHM.setSliderStyle(Slider::Rotary);
	sliderQualityHM.setRange(0.1f, 2.0f, 0.05); 
	sliderQualityHM.setValue(processor.getQualityValue(2));
	sliderQualityHM.setTextBoxStyle(Slider::TextBoxAbove, true, 80, 20);
	sliderQualityHM.setTextBoxIsEditable(true);

	sliderQualityHM.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqHM.getValue(), sliderQualityHM.getValue(), sliderGainHM.getValue(), 2);
	};
	addAndMakeVisible(&sliderQualityHM);


	sliderGainHM.setSliderStyle(Slider::Rotary);
	sliderGainHM.setRange(-30.0f, 30.0f, 1.0f);
	sliderGainHM.setValue(processor.getGainValue(2));
	sliderGainHM.setTextValueSuffix("dB");
	sliderGainHM.setTextBoxStyle(Slider::TextBoxAbove, true, 80, 20);
	sliderGainHM.setTextBoxIsEditable(true);

	sliderGainHM.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqHM.getValue(), sliderQualityHM.getValue(), sliderGainHM.getValue(), 2);
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
		processor.updateFilter(sliderFreqH.getValue(), sliderQualityH.getValue(), sliderGainH.getValue(), 3);

	};
	addAndMakeVisible(&sliderFreqH);


	sliderQualityH.setSliderStyle(Slider::Rotary);
	sliderQualityH.setRange(0.1f, 2.0f, 0.05);
	sliderQualityH.setValue(processor.getQualityValue(3));
	sliderQualityH.setTextBoxStyle(Slider::TextBoxAbove, true, 80, 20);
	sliderQualityH.setTextBoxIsEditable(true);

	sliderQualityH.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqH.getValue(), sliderQualityH.getValue(), sliderGainH.getValue(), 3);
	};
	addAndMakeVisible(&sliderQualityH);

	sliderGainH.setSliderStyle(Slider::Rotary);
	sliderGainH.setTextValueSuffix("dB");
	sliderGainH.setRange(-30.0f, 30.0f, 1.0f); 
	sliderGainH.setValue(processor.getGainValue(3));
	sliderGainH.setTextBoxStyle(Slider::TextBoxAbove, true, 80, 20);
	sliderGainH.setTextBoxIsEditable(true);

	sliderGainH.onValueChange = [this]
	{
		processor.updateFilter(sliderFreqH.getValue(), sliderQualityH.getValue(), sliderGainH.getValue(), 3);
	};
	addAndMakeVisible(&sliderGainH);

	btnFilterTypeH.setButtonText(processor.getFilterTypeName(3));

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
		processor.updateFilter(sliderFreqH.getValue(), sliderQualityH.getValue(), sliderGainH.getValue(), 3); 
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
	g.fillRect(0, 260, 100, 400);
	g.setColour(Colours::darkgrey);
	g.fillRect(100, 260,225,400);
	g.setColour(Colours::darkcyan);
	g.fillRect(325, 260, 225, 400);
	g.setColour(Colours::darkgrey);
	g.fillRect(550, 260, 225, 400);
	g.setColour(Colours::darkcyan);
	g.fillRect(775, 260, 225, 400);
	g.setOpacity(1.0f);

	g.setColour(Colours::white);
	g.setFont(16);
	g.drawText("PEAK", 420, 260, 50, 30, Justification::centred);
	g.drawText("PEAK", 640, 260, 50, 30,Justification::centred );

	g.setFont(15);
	g.drawText("FILTER TYPE", 10, 260, 100, 30, Justification::left);


	g.setFont(26);
	g.drawText("F", 20, 320, 50, 30, Justification::centred);
	g.drawText("Q", 20, 420, 50, 30, Justification::centred);
	g.drawText("G", 20, 520, 50, 30, Justification::centred);


	g.setFont(10);
	g.drawText("CHANGE", 245, 255, 100, 30, Justification::left);
	g.drawText("TYPE", 245, 267, 100, 30, Justification::left);
	g.drawText("CHANGE", 915, 255, 100, 30, Justification::left);
	g.drawText("TYPE", 915, 267, 100, 30, Justification::left);



	sc.prepareToPaintSpectrum(processor.getFFTSize(), processor.getFFTData());


}

void Eq_spectrumAudioProcessorEditor::resized()
{
	buttonWindow.setBounds(0, 0, 100, 30);
	sc.setBounds(0, 20, 1000, 260);  // -


	btnFilterTypeL.setBounds(190, 265, 50, 25);
	sliderFreqL.setBounds(160, 300, 100, 100);
	sliderQualityL.setBounds(160, 400, 100, 100);
	sliderGainL.setBounds(160, 500, 100, 100);


	sliderFreqLM.setBounds(390, 300, 100, 100);
	sliderQualityLM.setBounds(390, 400, 100, 100);
	sliderGainLM.setBounds(390, 500, 100, 100);

	sliderFreqHM.setBounds(610, 300, 100, 100);
	sliderQualityHM.setBounds(610, 400, 100, 100);
	sliderGainHM.setBounds(610, 500, 100, 100);

	btnFilterTypeH.setBounds(860, 265, 50, 25);
	sliderFreqH.setBounds(830, 300, 100, 100);
	sliderQualityH.setBounds(830, 400, 100, 100);
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


