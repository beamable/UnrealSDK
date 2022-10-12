

#include "OptionalPeriodLibrary.h"

FOptionalPeriod UOptionalPeriodLibrary::MakeOptionalPeriod(UPeriod* Value)
{
	FOptionalPeriod Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalPeriod UOptionalPeriodLibrary::Conv_OptionalPeriodFromValue(UPeriod* Value)
{
	FOptionalPeriod Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

