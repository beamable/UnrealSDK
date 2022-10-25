

#include "AutoGen/Optionals/OptionalMapOfStringLibrary.h"

FOptionalMapOfString UOptionalMapOfStringLibrary::MakeOptional(TMap<FString, FString> Value)
{
	FOptionalMapOfString Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalMapOfString UOptionalMapOfStringLibrary::Conv_OptionalFromValue(TMap<FString, FString> Value)
{
	FOptionalMapOfString Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalMapOfStringLibrary::HasValue(const FOptionalMapOfString& Optional, TMap<FString, FString>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TMap<FString, FString> UOptionalMapOfStringLibrary::GetOptionalValue(const FOptionalMapOfString& Optional, TMap<FString, FString> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

