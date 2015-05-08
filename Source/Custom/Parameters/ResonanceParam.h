/*
  ==============================================================================

	ResonanceParam.h
	Created: 8 May 2015 11:16:20am
	Author:  Jordan

  ==============================================================================
*/

#ifndef RESONANCEPARAM_H_INCLUDED
#define RESONANCEPARAM_H_INCLUDED

#include "../../JuceLibraryCode/JuceHeader.h"
#include "FloatParameter.h"
#include "../TransDirectFormIIFilter.h"

//==============================================================================
class ResonanceParam : public FloatParameter {
public:
	ResonanceParam(TransDirectFormIIFilter& filter,
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

		directFormFilter.setResonance(newValue);
	}

private:
	TransDirectFormIIFilter& directFormFilter;
};

//==============================================================================
#endif  // RESONANCEPARAM_H_INCLUDED
