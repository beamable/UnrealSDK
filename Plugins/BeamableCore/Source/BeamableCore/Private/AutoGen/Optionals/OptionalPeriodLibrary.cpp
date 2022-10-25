

#include "AutoGen/Optionals/OptionalPeriodLibrary.h"

FOptionalPeriod UOptionalPeriodLibrary::MakeOptional(UPeriod* Value)
{
	FOptionalPeriod Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalPeriod UOptionalPeriodLibrary::Conv_OptionalFromValue(UPeriod* Value)
{
	FOptionalPeriod Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalPeriodLibrary::HasValue(const FOptionalPeriod& Optional, UPeriod*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UPeriod* UOptionalPeriodLibrary::GetOptionalValue(const FOptionalPeriod& Optional, UPeriod* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

