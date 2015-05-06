/*
  ==============================================================================

	TransDirectFormIIFilter.cpp
	Created: 28 Apr 2015 3:16:59pm
	Author:  Jordan

  ==============================================================================
*/

#include "TransDirectFormIIFilter.h"

//==============================================================================
TransDirectFormIIFilter::TransDirectFormIIFilter()
{
	sampleRate = 44100;					// default sample rate when constructed
	type = bq_type_lowpass;				// lowpass filter by default
	a0 = 1.0;
	a1 = a2 = b1 = b2 = 0.0;
	Fc = pitchToFreq(5000.0) / sampleRate;
	Q = 1.0 / (2.0 * (1.0 - 0.7));		// default resonance: 0.7
	
	peakGain = 0.0;
	z1_A[0] = z2_A[0] = 0.0;
	z1_A[1] = z2_A[1] = 0.0;
}

TransDirectFormIIFilter::TransDirectFormIIFilter(int type, double Fc, double res,
												 double peakGaindB)
{
	setFilter(type, Fc, res, peakGaindB);
	z1_A[0] = z2_A[0] = 0.0;
	z1_A[1] = z2_A[1] = 0.0;
}

TransDirectFormIIFilter::~TransDirectFormIIFilter()
{
}

void TransDirectFormIIFilter::setType(int type) {
	this->type = type;
	calcFilter();
}

void TransDirectFormIIFilter::setResonance(double resonance)
{
	this->Q = 1.0 / (2.0 * (1.0 - resonance));
	calcFilter();
}

void TransDirectFormIIFilter::setFc(double Fc)
{
	this->Fc = pitchToFreq(Fc) / sampleRate;
	calcFilter();
}

	void TransDirectFormIIFilter::setPeakGain(double peakGaindB)
{
	this->peakGain = peakGaindB;
	calcFilter();
}

void TransDirectFormIIFilter::setFilter(int type, double Fc, double resonance,
										double peakGaindB)
{
	this->type = type;
	this->Q = 1.0 / (2.0 * (1.0 - resonance));
	this->Fc = pitchToFreq(Fc);
	setPeakGain(peakGaindB);
}

void TransDirectFormIIFilter::setSampleRate(double sampleRate)
{
	
	this->sampleRate = sampleRate;
	calcFilter();
}

void TransDirectFormIIFilter::calcFilter(void)
{
	
	double norm;
	double V = pow(10, fabs(peakGain) / 20.0);
	double K = tan(M_PI * Fc);
	switch (this->type) {
	case bq_type_lowpass:
		norm = 1 / (1 + K / Q + K * K);
		a0 = K * K * norm;
		a1 = 2 * a0;
		a2 = a0;
		b1 = 2 * (K * K - 1) * norm;
		b2 = (1 - K / Q + K * K) * norm;
		break;

	case bq_type_highpass:
		norm = 1 / (1 + K / Q + K * K);
		a0 = 1 * norm;
		a1 = -2 * a0;
		a2 = a0;
		b1 = 2 * (K * K - 1) * norm;
		b2 = (1 - K / Q + K * K) * norm;
		break;

	case bq_type_bandpass:
		norm = 1 / (1 + K / Q + K * K);
		a0 = K / Q * norm;
		a1 = 0;
		a2 = -a0;
		b1 = 2 * (K * K - 1) * norm;
		b2 = (1 - K / Q + K * K) * norm;
		break;

	case bq_type_notch:
		norm = 1 / (1 + K / Q + K * K);
		a0 = (1 + K * K) * norm;
		a1 = 2 * (K * K - 1) * norm;
		a2 = a0;
		b1 = a1;
		b2 = (1 - K / Q + K * K) * norm;
		break;

	case bq_type_peak:
		if (peakGain >= 0) {	// boost
			norm = 1 / (1 + 1 / Q * K + K * K);
			a0 = (1 + V / Q * K + K * K) * norm;
			a1 = 2 * (K * K - 1) * norm;
			a2 = (1 - V / Q * K + K * K) * norm;
			b1 = a1;
			b2 = (1 - 1 / Q * K + K * K) * norm;
		}
		else {					// cut
			norm = 1 / (1 + V / Q * K + K * K);
			a0 = (1 + 1 / Q * K + K * K) * norm;
			a1 = 2 * (K * K - 1) * norm;
			a2 = (1 - 1 / Q * K + K * K) * norm;
			b1 = a1;
			b2 = (1 - V / Q * K + K * K) * norm;
		}
		break;

	case bq_type_lowshelf:
		if (peakGain >= 0) {	// boost
			norm = 1 / (1 + sqrt(2) * K + K * K);
			a0 = (1 + sqrt(2 * V) * K + V * K * K) * norm;
			a1 = 2 * (V * K * K - 1) * norm;
			a2 = (1 - sqrt(2 * V) * K + V * K * K) * norm;
			b1 = 2 * (K * K - 1) * norm;
			b2 = (1 - sqrt(2) * K + K * K) * norm;
		}
		else {					// cut
			norm = 1 / (1 + sqrt(2 * V) * K + V * K * K);
			a0 = (1 + sqrt(2) * K + K * K) * norm;
			a1 = 2 * (K * K - 1) * norm;
			a2 = (1 - sqrt(2) * K + K * K) * norm;
			b1 = 2 * (V * K * K - 1) * norm;
			b2 = (1 - sqrt(2 * V) * K + V * K * K) * norm;
		}
		break;

	case bq_type_highshelf:
		if (peakGain >= 0) {	// boost
			norm = 1 / (1 + sqrt(2) * K + K * K);
			a0 = (V + sqrt(2 * V) * K + K * K) * norm;
			a1 = 2 * (K * K - V) * norm;
			a2 = (V - sqrt(2 * V) * K + K * K) * norm;
			b1 = 2 * (K * K - 1) * norm;
			b2 = (1 - sqrt(2) * K + K * K) * norm;
		}
		else {					// cut
			norm = 1 / (V + sqrt(2 * V) * K + K * K);
			a0 = (1 + sqrt(2) * K + K * K) * norm;
			a1 = 2 * (K * K - 1) * norm;
			a2 = (1 - sqrt(2) * K + K * K) * norm;
			b1 = 2 * (K * K - V) * norm;
			b2 = (V - sqrt(2 * V) * K + K * K) * norm;
		}
		break;
	}
	return;
}

//==============================================================================
