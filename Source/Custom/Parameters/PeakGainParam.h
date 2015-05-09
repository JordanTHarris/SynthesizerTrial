/*
  ==============================================================================

	PeakGainParam.h
	Created: 8 May 2015 11:16:42am
	Author:  Jordan

  ==============================================================================
*/

#ifndef PEAKGAINPARAM_H_INCLUDED
#define PEAKGAINPARAM_H_INCLUDED

#include "../../JuceLibraryCode/JuceHeader.h"
#include "FloatParameter.h"
#include "../TransDirectFormIIFilter.h"

//==============================================================================

class PeakGainParam : public FloatParameter {
public:
	PeakGainParam(TransDirectFormIIFilter& filter,
		float defaultParamVal,
		const String& paramName)
		: FloatParameter(defaultParamVal, paramName),
		directFormFilter{ filter }
	{
	}

	void setValue(float newValue) override
	{
		// call the base class
		FloatParameter::setValue(newValue);

		// Conver normalized values (0->1) to gain values (-60dB->10dB)
		const float realGain = xFadeLin(newValue, -60, 10);

		directFormFilter.setPeakGain(newValue);
	}

private:
	TransDirectFormIIFilter& directFormFilter;
};

//==============================================================================
#endif  // PEAKGAINPARAM_H_INCLUDED
