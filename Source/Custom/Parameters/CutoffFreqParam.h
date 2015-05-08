/*
  ==============================================================================

	CutoffFreqParam.h
	Created: 8 May 2015 10:54:56am
	Author:  Jordan

  ==============================================================================
*/

#ifndef CUTOFFFREQPARAM_H_INCLUDED
#define CUTOFFFREQPARAM_H_INCLUDED

#include "../../JuceLibraryCode/JuceHeader.h"
#include "FloatParameter.h"
#include "../TransDirectFormIIFilter.h"


//==============================================================================
class CutoffFreqParam : public FloatParameter {
public:
	CutoffFreqParam(TransDirectFormIIFilter& filter, 
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

		// Convert normalized value (0->1) to pitch values
		const float realCutoff = xFadeLin(newValue, 22, 130);

		directFormFilter.setCutoff(realCutoff);
	}

private:
	TransDirectFormIIFilter& directFormFilter;
};

//==============================================================================
#endif  // CUTOFFFREQPARAM_H_INCLUDED
