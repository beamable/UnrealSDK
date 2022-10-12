

#include "OptionalDoubleLibrary.h"

FOptionalDouble UOptionalDoubleLibrary::MakeOptionalDouble(double Value)
{
	FOptionalDouble Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalDouble UOptionalDoubleLibrary::Conv_OptionalDoubleFromValue(double Value)
{
	FOptionalDouble Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

