

#include "OptionalBoolLibrary.h"

FOptionalBool UOptionalBoolLibrary::MakeOptionalBool(bool Value)
{
	FOptionalBool Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalBool UOptionalBoolLibrary::Conv_OptionalBoolFromValue(bool Value)
{
	FOptionalBool Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

