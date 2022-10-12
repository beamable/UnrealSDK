

#include "OptionalInt64Library.h"

FOptionalInt64 UOptionalInt64Library::MakeOptionalInt64(int64 Value)
{
	FOptionalInt64 Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalInt64 UOptionalInt64Library::Conv_OptionalInt64FromValue(int64 Value)
{
	FOptionalInt64 Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

