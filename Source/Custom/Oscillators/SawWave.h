/*
  ==============================================================================

	SawWave.h
	Created: 8 May 2015 3:33:03pm
	Author:  Jordan

  ==============================================================================
*/

#ifndef SAWWAVE_H_INCLUDED
#define SAWWAVE_H_INCLUDED

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================

class SawWaveSound : public SynthesiserSound {
public:
	SawWaveSound() {}

	bool appliesToNote(int midiNoteNumber) override { return true; }
	bool appliesToChannel(int midiChannel) override { return true; }
};

class SawWaveVoice : public SynthesiserVoice {
public:
	SawWaveVoice();
	bool canPlaySound(SynthesiserSound* sound) override;
	void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound,
		int currentPitchWheelPosition) override;
	void stopNote(float velocity, bool allowTailOff) override;
	void pitchWheelMoved(int newValue) override;
	void controllerMoved(int controllerNumber, int newValue) override;
	void renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples);

private:
	double frequency;
	double phaseShift;
	double level;
	double tailOff;
	double currentPhase;
	double normalizedFreq;	// Normalized Fundamental Frequency
	double wrapValue;		// Number the accumulator will wrap around (N)
							// N = 0.5 (Ramp)
							// N = Pi (Sine)

};

//==============================================================================
#endif  // SAWWAVE_H_INCLUDED
