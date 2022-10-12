

#include "OptionalMapOfInt64Library.h"

FOptionalMapOfInt64 UOptionalMapOfInt64Library::MakeOptionalMapOfInt64(TMap<FString, int64> Value)
{
	FOptionalMapOfInt64 Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalMapOfInt64 UOptionalMapOfInt64Library::Conv_OptionalMapOfInt64FromValue(TMap<FString, int64> Value)
{
	FOptionalMapOfInt64 Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

