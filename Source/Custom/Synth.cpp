/*
  ==============================================================================

	Synth.cpp
	Created: 2 May 2015 3:48:07am
	Author:  Jordan

  ==============================================================================
*/

#include "Synth.h"

SineWaveVoice::SineWaveVoice()
	: angleDelta{ 0.0 }, 
	  tailOff{0.0}
{
}

bool SineWaveVoice::canPlaySound(SynthesiserSound* sound)
{
	return dynamic_cast<SineWaveSound*> (sound) != nullptr;
}

void SineWaveVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound,
	int currentPitchWheelPosition)
{
	currentAngle = 0.0;
	level = velocity * 0.15;
	tailOff = 0.0;

	double cyclesPerSecond = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
	double cyclesPerSamples = cyclesPerSecond / getSampleRate();

	angleDelta = cyclesPerSamples * 2.0 * double_Pi;
}

void SineWaveVoice::stopNote(float velocity, bool allowTailOff)
{
	if (allowTailOff) {
		// start a tail-off by setting this flag. The render callback will pick up
		// on this and do a fade out, calling clearCurrentNote() when it's finished.

		// we only need to begin a tail-off if it's not already doing so - the
		// stopNote method could be called more than once.
		if (tailOff == 0.0)
			tailOff = 1.0;
	}
	else {
		// we're being told to stop playing immediately, so reset everything...
		clearCurrentNote();
		angleDelta = 0.0;
	}
}

void SineWaveVoice::pitchWheelMoved(int newValue)
{

}

void SineWaveVoice::controllerMoved(int controllerNumber, int newValue)
{

}

void SineWaveVoice::renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
{
	if (angleDelta != 0.0) {
		if (tailOff > 0) {
			while (--numSamples >= 0) {
				const float currentSample = (float)(sin(currentAngle) * level * tailOff);

				for (int i = outputBuffer.getNumChannels(); --i >= 0;)
					outputBuffer.addSample(i, startSample, currentSample);

				currentAngle += angleDelta;
				++startSample;

				tailOff *= 0.99;

				if (tailOff <= 0.005) {
					clearCurrentNote();

					angleDelta = 0.0;
					break;
				}
			}
		}
		else {
			while (--numSamples >= 0) {
				const float currentSample = (float)(sin(currentAngle) * level);

				for (int i = outputBuffer.getNumChannels(); --i >= 0;)
					outputBuffer.addSample(i, startSample, currentSample);

				currentAngle += angleDelta;
				++startSample;
			}
		}
	}
}
