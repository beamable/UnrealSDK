

#include "AutoGen/Optionals/OptionalMapOfInt64Library.h"

FOptionalMapOfInt64 UOptionalMapOfInt64Library::MakeOptional(TMap<FString, int64> Value)
{
	FOptionalMapOfInt64 Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalMapOfInt64 UOptionalMapOfInt64Library::Conv_OptionalFromValue(TMap<FString, int64> Value)
{
	FOptionalMapOfInt64 Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalMapOfInt64Library::HasValue(const FOptionalMapOfInt64& Optional, TMap<FString, int64>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TMap<FString, int64> UOptionalMapOfInt64Library::GetOptionalValue(const FOptionalMapOfInt64& Optional, TMap<FString, int64> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

