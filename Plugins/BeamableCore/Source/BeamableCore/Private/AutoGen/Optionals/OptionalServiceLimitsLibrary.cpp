

#include "AutoGen/Optionals/OptionalServiceLimitsLibrary.h"

FOptionalServiceLimits UOptionalServiceLimitsLibrary::MakeOptional(UServiceLimits* Value)
{
	FOptionalServiceLimits Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalServiceLimits UOptionalServiceLimitsLibrary::Conv_OptionalFromValue(UServiceLimits* Value)
{
	FOptionalServiceLimits Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalServiceLimitsLibrary::HasValue(const FOptionalServiceLimits& Optional, UServiceLimits*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UServiceLimits* UOptionalServiceLimitsLibrary::GetOptionalValue(const FOptionalServiceLimits& Optional, UServiceLimits* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

