

#include "OptionalStringLibrary.h"

FOptionalString UOptionalStringLibrary::MakeOptionalString(FString Value)
{
	FOptionalString Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalString UOptionalStringLibrary::Conv_OptionalStringFromValue(FString Value)
{
	FOptionalString Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

