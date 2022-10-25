

#include "AutoGen/Optionals/OptionalInt64Library.h"

FOptionalInt64 UOptionalInt64Library::MakeOptional(int64 Value)
{
	FOptionalInt64 Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalInt64 UOptionalInt64Library::Conv_OptionalFromValue(int64 Value)
{
	FOptionalInt64 Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalInt64Library::HasValue(const FOptionalInt64& Optional, int64& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

int64 UOptionalInt64Library::GetOptionalValue(const FOptionalInt64& Optional, int64 DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

