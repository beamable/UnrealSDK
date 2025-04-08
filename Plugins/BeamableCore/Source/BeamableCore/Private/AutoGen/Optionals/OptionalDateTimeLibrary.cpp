

#include "AutoGen/Optionals/OptionalDateTimeLibrary.h"

FOptionalDateTime UOptionalDateTimeLibrary::MakeOptional(FDateTime Value)
{
	FOptionalDateTime Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalDateTime UOptionalDateTimeLibrary::Conv_OptionalFromValue(FDateTime Value)
{
	FOptionalDateTime Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalDateTimeLibrary::HasValue(const FOptionalDateTime& Optional, FDateTime& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

FDateTime UOptionalDateTimeLibrary::GetOptionalValue(const FOptionalDateTime& Optional, FDateTime DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

