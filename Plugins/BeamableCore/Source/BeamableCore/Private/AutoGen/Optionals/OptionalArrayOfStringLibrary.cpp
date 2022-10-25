

#include "AutoGen/Optionals/OptionalArrayOfStringLibrary.h"

FOptionalArrayOfString UOptionalArrayOfStringLibrary::MakeOptional(TArray<FString> Value)
{
	FOptionalArrayOfString Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfString UOptionalArrayOfStringLibrary::Conv_OptionalFromValue(TArray<FString> Value)
{
	FOptionalArrayOfString Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfStringLibrary::HasValue(const FOptionalArrayOfString& Optional, TArray<FString>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<FString> UOptionalArrayOfStringLibrary::GetOptionalValue(const FOptionalArrayOfString& Optional, TArray<FString> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

