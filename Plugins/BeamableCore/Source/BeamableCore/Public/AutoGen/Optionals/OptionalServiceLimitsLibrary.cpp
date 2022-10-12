

#include "OptionalServiceLimitsLibrary.h"

FOptionalServiceLimits UOptionalServiceLimitsLibrary::MakeOptionalServiceLimits(UServiceLimits* Value)
{
	FOptionalServiceLimits Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalServiceLimits UOptionalServiceLimitsLibrary::Conv_OptionalServiceLimitsFromValue(UServiceLimits* Value)
{
	FOptionalServiceLimits Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

