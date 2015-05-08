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

//[Headers] You can add your own extra header files here...
#include "PluginProcessor.h"
#include "Custom\Utilities\DspUtilities.h"
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SynthesizerAudioProcessorEditor::SynthesizerAudioProcessorEditor (SynthesizerAudioProcessor& owner)
    : AudioProcessorEditor(owner), midiKeyboard(owner.keyboardState, MidiKeyboardComponent::horizontalKeyboard)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (outGainSlider = new Slider ("Output Gain"));
    outGainSlider->setRange (0, 1, 0);
    outGainSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    outGainSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    outGainSlider->addListener (this);

    addAndMakeVisible (semitoneSlider = new Slider ("Semitones"));
    semitoneSlider->setTooltip (TRANS("Controls the pitch of the oscillator in semitones"));
    semitoneSlider->setRange (0, 1, 0);
    semitoneSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    semitoneSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    semitoneSlider->addListener (this);

    addAndMakeVisible (centsSlider = new Slider ("Cents"));
    centsSlider->setTooltip (TRANS("Controls the pitch of the oscillator in cents."));
    centsSlider->setRange (0, 1, 0);
    centsSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    centsSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    centsSlider->addListener (this);

    addAndMakeVisible (cutoffSlider = new Slider ("Cutoff"));
    cutoffSlider->setTooltip (TRANS("Logarithmic control of the filter\'s cutoff frequency."));
    cutoffSlider->setRange (0, 1, 0);
    cutoffSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    cutoffSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    cutoffSlider->addListener (this);

    addAndMakeVisible (resonanceSlider = new Slider ("Resonance"));
    resonanceSlider->setTooltip (TRANS("Filter\'s resonance control. Self-oscillation at 1.0."));
    resonanceSlider->setRange (0, 1, 0);
    resonanceSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    resonanceSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    resonanceSlider->addListener (this);

    addAndMakeVisible (peakGainSlider = new Slider ("new slider"));
    peakGainSlider->setTooltip (TRANS("Peak gain for the Peak, Lowshelf, and Highshelf filters."));
    peakGainSlider->setRange (0, 1, 0);
    peakGainSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    peakGainSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    peakGainSlider->addListener (this);

    addAndMakeVisible (filterTypeCBox = new ComboBox ("Filter Type"));
    filterTypeCBox->setTooltip (TRANS("Select the filter type to use."));
    filterTypeCBox->setEditableText (false);
    filterTypeCBox->setJustificationType (Justification::centredLeft);
    filterTypeCBox->setTextWhenNothingSelected (String::empty);
    filterTypeCBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    filterTypeCBox->addItem (TRANS("Lowpass"), 1);
    filterTypeCBox->addItem (TRANS("Highpass"), 2);
    filterTypeCBox->addItem (TRANS("Bandpass"), 3);
    filterTypeCBox->addItem (TRANS("Notch"), 4);
    filterTypeCBox->addItem (TRANS("Peak"), 5);
    filterTypeCBox->addItem (TRANS("Lowshelf"), 6);
    filterTypeCBox->addItem (TRANS("Highshelf"), 7);
    filterTypeCBox->addListener (this);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Output Gain")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centred);
    label->setEditable (false, false, false);
    label->setColour (Label::textColourId, Colours::aliceblue);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Semitone")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centred);
    label2->setEditable (false, false, false);
    label2->setColour (Label::textColourId, Colours::aliceblue);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("Cents")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centred);
    label3->setEditable (false, false, false);
    label3->setColour (Label::textColourId, Colours::aliceblue);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("Cutoff")));
    label4->setFont (Font (15.00f, Font::plain));
    label4->setJustificationType (Justification::centred);
    label4->setEditable (false, false, false);
    label4->setColour (Label::textColourId, Colours::aliceblue);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label5 = new Label ("new label",
                                           TRANS("Resonance")));
    label5->setFont (Font (15.00f, Font::plain));
    label5->setJustificationType (Justification::centred);
    label5->setEditable (false, false, false);
    label5->setColour (Label::backgroundColourId, Colour (0x00000000));
    label5->setColour (Label::textColourId, Colours::aliceblue);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label6 = new Label ("new label",
                                           TRANS("Peak Gain")));
    label6->setFont (Font (15.00f, Font::plain));
    label6->setJustificationType (Justification::centred);
    label6->setEditable (false, false, false);
    label6->setColour (Label::textColourId, Colours::aliceblue);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    // add the triangular resizer component for the bottom-right of the UI
    addAndMakeVisible (resizer = new ResizableCornerComponent (this, &resizeLimits));
    resizeLimits.setSizeLimits (400, 300, 800, 300);
    //[/UserPreSize]

    setSize (400, 300);


    //[Constructor] You can add your own custom stuff here..
	addAndMakeVisible(midiKeyboard);

	startTimerHz(512);		// 512 Hz control rate

	setSize(owner.lastUIWidth, owner.lastUIHeight);

    //[/Constructor]
}

SynthesizerAudioProcessorEditor::~SynthesizerAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    outGainSlider = nullptr;
    semitoneSlider = nullptr;
    centsSlider = nullptr;
    cutoffSlider = nullptr;
    resonanceSlider = nullptr;
    peakGainSlider = nullptr;
    filterTypeCBox = nullptr;
    label = nullptr;
    label2 = nullptr;
    label3 = nullptr;
    label4 = nullptr;
    label5 = nullptr;
    label6 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SynthesizerAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff2b2b2b));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SynthesizerAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    outGainSlider->setBounds (312, 40, 50, 50);
    semitoneSlider->setBounds (16, 40, 50, 50);
    centsSlider->setBounds (88, 40, 50, 50);
    cutoffSlider->setBounds (16, 128, 50, 50);
    resonanceSlider->setBounds (88, 128, 50, 50);
    peakGainSlider->setBounds (160, 128, 50, 50);
    filterTypeCBox->setBounds (240, 136, 128, 24);
    label->setBounds (304, 8, 64, 24);
    label2->setBounds (8, 8, 64, 24);
    label3->setBounds (80, 8, 64, 24);
    label4->setBounds (8, 96, 64, 24);
    label5->setBounds (80, 96, 64, 24);
    label6->setBounds (152, 96, 64, 24);
    //[UserResized] Add your own custom resize handling here..
	const int keyboardHeight = 70;
	midiKeyboard.setBounds(4, getHeight() - keyboardHeight - 12, getWidth() - 8, keyboardHeight);

	resizer->setBounds(getWidth() - 16, getHeight() - 16, 16, 16);

	getProcessor().lastUIWidth = getWidth();
	getProcessor().lastUIHeight = getHeight();
    //[/UserResized]
}

void SynthesizerAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
	if (AudioProcessorParameter* param = getParameterFromSlider(sliderThatWasMoved))
	{
		// It's vital to use setValueNotifyingHost to change any parameters that are automatable
		// by the host, rather than just modifying them directly, otherwise the host won't know
		// that they've changed.
		param->setValueNotifyingHost((float)sliderThatWasMoved->getValue());
	}
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == outGainSlider)
    {
        //[UserSliderCode_outGainSlider] -- add your slider handling code here..
        //[/UserSliderCode_outGainSlider]
    }
    else if (sliderThatWasMoved == semitoneSlider)
    {
        //[UserSliderCode_semitoneSlider] -- add your slider handling code here..
        //[/UserSliderCode_semitoneSlider]
    }
    else if (sliderThatWasMoved == centsSlider)
    {
        //[UserSliderCode_centsSlider] -- add your slider handling code here..
        //[/UserSliderCode_centsSlider]
    }
    else if (sliderThatWasMoved == cutoffSlider)
    {
        //[UserSliderCode_cutoffSlider] -- add your slider handling code here..
        //[/UserSliderCode_cutoffSlider]
    }
    else if (sliderThatWasMoved == resonanceSlider)
    {
        //[UserSliderCode_resonanceSlider] -- add your slider handling code here..
        //[/UserSliderCode_resonanceSlider]
    }
    else if (sliderThatWasMoved == peakGainSlider)
    {
        //[UserSliderCode_peakGainSlider] -- add your slider handling code here..
        //[/UserSliderCode_peakGainSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void SynthesizerAudioProcessorEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
	if (AudioProcessorParameter* param = getParameterFromComboBox(comboBoxThatHasChanged))
	{
		//param->setValueNotifyingHost((float)comboBoxThatHasChanged->getSelectedItemIndex());
	}
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == filterTypeCBox)
    {
        //[UserComboBoxCode_filterTypeCBox] -- add your combo box handling code here..

        //[/UserComboBoxCode_filterTypeCBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

// Parameter handling and updating methods (AudioProcessorParameter):
//==============================================================================
void SynthesizerAudioProcessorEditor::timerCallback()
{
	SynthesizerAudioProcessor& ourProcessor = getProcessor();

	AudioPlayHead::CurrentPositionInfo newPos(ourProcessor.lastPosInfo);


	outGainSlider->setValue(ourProcessor.outputGain->getValue(), dontSendNotification);
	semitoneSlider->setValue(ourProcessor.semitones->getValue(), dontSendNotification);
	centsSlider->setValue(ourProcessor.cents->getValue(), dontSendNotification);
	cutoffSlider->setValue(ourProcessor.cutoff->getValue(), dontSendNotification);
	resonanceSlider->setValue(ourProcessor.resonance->getValue(), dontSendNotification);
	peakGainSlider->setValue(ourProcessor.peakGaindB->getValue(), dontSendNotification);

	//filterTypeCBox->setSelectedItemIndex(ourProcessor.filterType->getValue(), dontSendNotification);
}

void SynthesizerAudioProcessorEditor::sliderDragStarted(Slider* slider)
{
    if (AudioProcessorParameter* param = getParameterFromSlider (slider))
    {
        param->beginChangeGesture();
    }
}

void SynthesizerAudioProcessorEditor::sliderDragEnded(Slider* slider)
{
    if (AudioProcessorParameter* param = getParameterFromSlider (slider))
    {
        param->endChangeGesture();
    }
}

AudioProcessorParameter* SynthesizerAudioProcessorEditor::getParameterFromSlider(const Slider* slider) const
{
	if (outGainSlider == slider)
		return getProcessor().outputGain;

	if (semitoneSlider == slider)
		return getProcessor().semitones;

	if (centsSlider == slider)
		return getProcessor().cents;

	if (cutoffSlider == slider)
		return getProcessor().cutoff;

	if (resonanceSlider == slider)
		return getProcessor().resonance;

	if (peakGainSlider == slider)
		return getProcessor().peakGaindB;

	return nullptr;		// if none of the above are true
}


AudioProcessorParameter* SynthesizerAudioProcessorEditor::getParameterFromComboBox(const ComboBox* comboBox) const
{
	if (filterTypeCBox == comboBox)
		//return getProcessor().filterType;

	return nullptr;
}


//==============================================================================
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SynthesizerAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="SynthesizerAudioProcessor&amp; owner" variableInitialisers="AudioProcessorEditor(owner), midiKeyboard(owner.keyboardState, MidiKeyboardComponent::horizontalKeyboard)&#10;"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="400" initialHeight="300">
  <BACKGROUND backgroundColour="ff2b2b2b"/>
  <SLIDER name="Output Gain" id="2e20bf4c1f07b20c" memberName="outGainSlider"
          virtualName="" explicitFocusOrder="0" pos="312 40 50 50" min="0"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Semitones" id="fb201f827f7d2f2c" memberName="semitoneSlider"
          virtualName="" explicitFocusOrder="0" pos="16 40 50 50" tooltip="Controls the pitch of the oscillator in semitones"
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Cents" id="3f1ff092b335ad19" memberName="centsSlider" virtualName=""
          explicitFocusOrder="0" pos="88 40 50 50" tooltip="Controls the pitch of the oscillator in cents."
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Cutoff" id="5abac1c96a334c03" memberName="cutoffSlider"
          virtualName="" explicitFocusOrder="0" pos="16 128 50 50" tooltip="Logarithmic control of the filter's cutoff frequency."
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Resonance" id="7d338e3994abce10" memberName="resonanceSlider"
          virtualName="" explicitFocusOrder="0" pos="88 128 50 50" tooltip="Filter's resonance control. Self-oscillation at 1.0."
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="new slider" id="a37ba05311ec8299" memberName="peakGainSlider"
          virtualName="" explicitFocusOrder="0" pos="160 128 50 50" tooltip="Peak gain for the Peak, Lowshelf, and Highshelf filters."
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <COMBOBOX name="Filter Type" id="7e87e80d8b5b419" memberName="filterTypeCBox"
            virtualName="" explicitFocusOrder="0" pos="240 136 128 24" tooltip="Select the filter type to use."
            editable="0" layout="33" items="Lowpass&#10;Highpass&#10;Bandpass&#10;Notch&#10;Peak&#10;Lowshelf&#10;Highshelf"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="31ba3972b1999f82" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="304 8 64 24" textCol="fff0f8ff" edTextCol="ff000000"
         edBkgCol="0" labelText="Output Gain" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="b646518e25a85290" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="8 8 64 24" textCol="fff0f8ff" edTextCol="ff000000"
         edBkgCol="0" labelText="Semitone" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="86c6d4222b12b5dc" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="80 8 64 24" textCol="fff0f8ff" edTextCol="ff000000"
         edBkgCol="0" labelText="Cents" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="6fae448dc9b4739b" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="8 96 64 24" textCol="fff0f8ff" edTextCol="ff000000"
         edBkgCol="0" labelText="Cutoff" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="1e7b77c10f2ca811" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="80 96 64 24" bkgCol="0" textCol="fff0f8ff"
         edTextCol="ff000000" edBkgCol="0" labelText="Resonance" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="8c99c231fa280c32" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="152 96 64 24" textCol="fff0f8ff"
         edTextCol="ff000000" edBkgCol="0" labelText="Peak Gain" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
