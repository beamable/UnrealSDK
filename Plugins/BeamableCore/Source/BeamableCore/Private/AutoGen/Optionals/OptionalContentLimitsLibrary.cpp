

#include "AutoGen/Optionals/OptionalContentLimitsLibrary.h"

FOptionalContentLimits UOptionalContentLimitsLibrary::MakeOptional(UContentLimits* Value)
{
	FOptionalContentLimits Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalContentLimits UOptionalContentLimitsLibrary::Conv_OptionalFromValue(UContentLimits* Value)
{
	FOptionalContentLimits Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalContentLimitsLibrary::HasValue(const FOptionalContentLimits& Optional, UContentLimits*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UContentLimits* UOptionalContentLimitsLibrary::GetOptionalValue(const FOptionalContentLimits& Optional, UContentLimits* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

