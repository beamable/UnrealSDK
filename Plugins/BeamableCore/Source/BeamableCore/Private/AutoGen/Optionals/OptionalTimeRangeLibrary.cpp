

#include "AutoGen/Optionals/OptionalTimeRangeLibrary.h"

FOptionalTimeRange UOptionalTimeRangeLibrary::MakeOptional(UTimeRange* Value)
{
	FOptionalTimeRange Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalTimeRange UOptionalTimeRangeLibrary::Conv_OptionalFromValue(UTimeRange* Value)
{
	FOptionalTimeRange Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalTimeRangeLibrary::HasValue(const FOptionalTimeRange& Optional, UTimeRange*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UTimeRange* UOptionalTimeRangeLibrary::GetOptionalValue(const FOptionalTimeRange& Optional, UTimeRange* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

