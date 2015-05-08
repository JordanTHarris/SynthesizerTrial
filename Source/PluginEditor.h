/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.1

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_DA5A6A9F108142D3__
#define __JUCE_HEADER_DA5A6A9F108142D3__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SynthesizerAudioProcessorEditor  : public AudioProcessorEditor,
                                         public Timer,
                                         public SliderListener,
                                         public ComboBoxListener
{
public:
    //==============================================================================
    SynthesizerAudioProcessorEditor (SynthesizerAudioProcessor& owner);
    ~SynthesizerAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void timerCallback();
	void sliderDragStarted(Slider*) override;
	void sliderDragEnded(Slider*) override;
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	MidiKeyboardComponent midiKeyboard;
	ScopedPointer<ResizableCornerComponent> resizer;
	ComponentBoundsConstrainer resizeLimits;

	AudioPlayHead::CurrentPositionInfo lastDisplayedPosition;

	//==============================================================================
	SynthesizerAudioProcessor& getProcessor() const
	{
		return static_cast<SynthesizerAudioProcessor&>(processor);
	}

	AudioProcessorParameter* getParameterFromSlider(const Slider*) const;
	AudioProcessorParameter* getParameterFromComboBox(const ComboBox*) const;

	void displayPositionInfo(const AudioPlayHead::CurrentPositionInfo& pos);


    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> outGainSlider;
    ScopedPointer<Slider> semitoneSlider;
    ScopedPointer<Slider> centsSlider;
    ScopedPointer<Slider> cutoffSlider;
    ScopedPointer<Slider> resonanceSlider;
    ScopedPointer<Slider> peakGainSlider;
    ScopedPointer<ComboBox> filterTypeCBox;
    ScopedPointer<Label> label;
    ScopedPointer<Label> label2;
    ScopedPointer<Label> label3;
    ScopedPointer<Label> label4;
    ScopedPointer<Label> label5;
    ScopedPointer<Label> label6;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthesizerAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_DA5A6A9F108142D3__
