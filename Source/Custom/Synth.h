/*
  ==============================================================================

	Synth.h
	Created: 2 May 2015 3:48:07am
	Author:  Jordan

  ==============================================================================
*/

#ifndef SYNTH_H_INCLUDED
#define SYNTH_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================

class SineWaveSound : public SynthesiserSound {
public:
	SineWaveSound() {}

	bool appliesToNote(int midiNoteNumber) override { return true; }
	bool appliesToChannel(int midiChannel) override { return true; }
};

class SineWaveVoice : public SynthesiserVoice {
public:
	SineWaveVoice();
	bool canPlaySound(SynthesiserSound* sound) override;
	void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound,
				   int currentPitchWheelPosition) override;
	void stopNote(float velocity, bool allowTailOff) override;
	void pitchWheelMoved(int newValue) override;
	void controllerMoved(int controllerNumber, int newValue) override;
	void renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples);

private:
	double currentAngle, angleDelta, level, tailOff;
};

//==============================================================================
#endif  // SYNTH_H_INCLUDED
