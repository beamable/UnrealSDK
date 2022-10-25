

#include "AutoGen/Optionals/OptionalInt32Library.h"

FOptionalInt32 UOptionalInt32Library::MakeOptional(int32 Value)
{
	FOptionalInt32 Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalInt32 UOptionalInt32Library::Conv_OptionalFromValue(int32 Value)
{
	FOptionalInt32 Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalInt32Library::HasValue(const FOptionalInt32& Optional, int32& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

int32 UOptionalInt32Library::GetOptionalValue(const FOptionalInt32& Optional, int32 DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

