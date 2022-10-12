

#include "OptionalInt32Library.h"

FOptionalInt32 UOptionalInt32Library::MakeOptionalInt32(int32 Value)
{
	FOptionalInt32 Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalInt32 UOptionalInt32Library::Conv_OptionalInt32FromValue(int32 Value)
{
	FOptionalInt32 Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

