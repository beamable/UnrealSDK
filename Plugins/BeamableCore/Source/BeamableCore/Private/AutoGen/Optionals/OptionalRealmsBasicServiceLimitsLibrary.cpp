

#include "AutoGen/Optionals/OptionalRealmsBasicServiceLimitsLibrary.h"

FOptionalRealmsBasicServiceLimits UOptionalRealmsBasicServiceLimitsLibrary::MakeOptional(URealmsBasicServiceLimits* Value)
{
	FOptionalRealmsBasicServiceLimits Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalRealmsBasicServiceLimits UOptionalRealmsBasicServiceLimitsLibrary::Conv_OptionalFromValue(URealmsBasicServiceLimits* Value)
{
	FOptionalRealmsBasicServiceLimits Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalRealmsBasicServiceLimitsLibrary::HasValue(const FOptionalRealmsBasicServiceLimits& Optional, URealmsBasicServiceLimits*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

URealmsBasicServiceLimits* UOptionalRealmsBasicServiceLimitsLibrary::GetOptionalValue(const FOptionalRealmsBasicServiceLimits& Optional, URealmsBasicServiceLimits* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

