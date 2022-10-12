

#include "OptionalArrayOfInt32Library.h"

FOptionalArrayOfInt32 UOptionalArrayOfInt32Library::MakeOptionalArrayOfInt32(TArray<int32> Value)
{
	FOptionalArrayOfInt32 Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfInt32 UOptionalArrayOfInt32Library::Conv_OptionalArrayOfInt32FromValue(TArray<int32> Value)
{
	FOptionalArrayOfInt32 Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

