

#include "AutoGen/Optionals/OptionalArrayOfInt64Library.h"

FOptionalArrayOfInt64 UOptionalArrayOfInt64Library::MakeOptional(TArray<int64> Value)
{
	FOptionalArrayOfInt64 Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfInt64 UOptionalArrayOfInt64Library::Conv_OptionalFromValue(TArray<int64> Value)
{
	FOptionalArrayOfInt64 Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfInt64Library::HasValue(const FOptionalArrayOfInt64& Optional, TArray<int64>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<int64> UOptionalArrayOfInt64Library::GetOptionalValue(const FOptionalArrayOfInt64& Optional, TArray<int64> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

