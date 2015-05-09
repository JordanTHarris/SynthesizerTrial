/*
  ==============================================================================

	FilterTypeParam.h
	Created: 8 May 2015 11:17:15am
	Author:  Jordan

  ==============================================================================
*/

#ifndef FILTERTYPEPARAM_H_INCLUDED
#define FILTERTYPEPARAM_H_INCLUDED

#include "../../JuceLibraryCode/JuceHeader.h"
#include "FloatParameter.h"
#include "../TransDirectFormIIFilter.h"

//==============================================================================

class FilterTypeParam : public FloatParameter {
public:
	FilterTypeParam(TransDirectFormIIFilter& filter,
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

		directFormFilter.setType(newValue);
	}

private:
	TransDirectFormIIFilter& directFormFilter;
};

//==============================================================================
#endif  // FILTERTYPEPARAM_H_INCLUDED
