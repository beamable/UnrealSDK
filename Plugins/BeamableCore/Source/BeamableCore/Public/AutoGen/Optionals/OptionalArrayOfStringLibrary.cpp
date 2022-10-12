

#include "OptionalArrayOfStringLibrary.h"

FOptionalArrayOfString UOptionalArrayOfStringLibrary::MakeOptionalArrayOfString(TArray<FString> Value)
{
	FOptionalArrayOfString Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfString UOptionalArrayOfStringLibrary::Conv_OptionalArrayOfStringFromValue(TArray<FString> Value)
{
	FOptionalArrayOfString Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

