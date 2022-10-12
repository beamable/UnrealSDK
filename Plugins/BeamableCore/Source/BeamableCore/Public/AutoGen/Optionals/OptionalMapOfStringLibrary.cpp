

#include "OptionalMapOfStringLibrary.h"

FOptionalMapOfString UOptionalMapOfStringLibrary::MakeOptionalMapOfString(TMap<FString, FString> Value)
{
	FOptionalMapOfString Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalMapOfString UOptionalMapOfStringLibrary::Conv_OptionalMapOfStringFromValue(TMap<FString, FString> Value)
{
	FOptionalMapOfString Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

