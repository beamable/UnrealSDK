

#include "OptionalArrayOfInt64Library.h"

FOptionalArrayOfInt64 UOptionalArrayOfInt64Library::MakeOptionalArrayOfInt64(TArray<int64> Value)
{
	FOptionalArrayOfInt64 Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfInt64 UOptionalArrayOfInt64Library::Conv_OptionalArrayOfInt64FromValue(TArray<int64> Value)
{
	FOptionalArrayOfInt64 Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

