/*
  ==============================================================================

	SawWave.cpp
	Created: 8 May 2015 3:33:03pm
	Author:  Jordan

  ==============================================================================
*/

/*
  ==============================================================================
	Digital sawtooth or ramp oscillator that can be controlled by a MIDI,
	changing the frequency. This could also be used as a phase accumulator
	with very slight modifications.

	Digital Sound Generation (part 1) pg. 3

	fo = Fundamental Frequency
	fs = Sample Rate (Default: 48 kHz. Double rate systems: 96 kHz.)
	T = Sampling Interval = 1/fs
	fn = 2Nfo/fs (Normalized Fundamental Frequency, ubiquitously used)
	φ = Phase shift in radians · N/π
	z^-1 = Delay of one T. Output changes in discrete time steps.
	wrap(x) = x-2N if x >= N, x+2N if x < -N, x otherwise, repeat until the result is
	within [-N, N) (Default: N = 1)

  ==============================================================================
*/
#include "SawWave.h"

//==============================================================================

SawWaveVoice::SawWaveVoice()
	: normalizedFreq{ 0.0 },
	tailOff{ 0.0 }
{
}

bool SawWaveVoice::canPlaySound(SynthesiserSound* sound)
{
	return dynamic_cast<SawWaveSound*> (sound) != nullptr;
}

void SawWaveVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound,
	int currentPitchWheelPosition)
{
	currentPhase = 0.0;
	level = velocity * 0.15;
	tailOff = 0.0;

	wrapValue = 0.5;		// Number the accumulator will wrap around (N)

	frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
	double sampleRate = getSampleRate();

	normalizedFreq = (frequency / sampleRate) * (2 * wrapValue);
}

void SawWaveVoice::stopNote(float velocity, bool allowTailOff)
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
		normalizedFreq = 0.0;
	}
}

void SawWaveVoice::pitchWheelMoved(int newValue)
{

}

void SawWaveVoice::controllerMoved(int controllerNumber, int newValue)
{

}

void SawWaveVoice::renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
{
	if (normalizedFreq != 0.0) {
		if (tailOff > 0) {
			while (--numSamples >= 0) {
				const float currentSample = (float)(currentPhase * level * tailOff);

				for (int i = outputBuffer.getNumChannels(); --i >= 0;)
					outputBuffer.addSample(i, startSample, currentSample);

				currentPhase += normalizedFreq;		// Summation (accumulate)

				++startSample;					// Next sample to add to buffer

				// Wrap accumulator (-wrapValue to wrapValue) or (-N to N)
				if (currentPhase >= wrapValue)
					currentPhase = currentPhase - (2 * wrapValue);
				else if (currentPhase < -wrapValue)
					currentPhase = currentPhase + (2 * wrapValue);

				tailOff *= 0.99;

				if (tailOff <= 0.005) {
					clearCurrentNote();

					normalizedFreq = 0.0;
					break;
				}

			}
		}
		else {
			while (--numSamples >= 0) {
				const float currentSample = (float)(sin(currentPhase) * level);

				for (int i = outputBuffer.getNumChannels(); --i >= 0;)
					outputBuffer.addSample(i, startSample, currentSample);

				currentPhase += normalizedFreq;		// Summation (accumulate)

				++startSample;					// Next sample to add to buffer

				// Wrap (-wrapValue to wrapValue) or (-N to N)
				if (currentPhase >= wrapValue)
					currentPhase = currentPhase - (2 * wrapValue);
				else if (currentPhase < -wrapValue)
					currentPhase = currentPhase + (2 * wrapValue);
			}
		}
	}
}

//==============================================================================
