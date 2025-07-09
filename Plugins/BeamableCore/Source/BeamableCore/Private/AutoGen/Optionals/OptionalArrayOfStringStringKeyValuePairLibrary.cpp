

#include "AutoGen/Optionals/OptionalArrayOfStringStringKeyValuePairLibrary.h"

FOptionalArrayOfStringStringKeyValuePair UOptionalArrayOfStringStringKeyValuePairLibrary::MakeOptional(TArray<UStringStringKeyValuePair*> Value)
{
	FOptionalArrayOfStringStringKeyValuePair Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfStringStringKeyValuePair UOptionalArrayOfStringStringKeyValuePairLibrary::Conv_OptionalFromValue(TArray<UStringStringKeyValuePair*> Value)
{
	FOptionalArrayOfStringStringKeyValuePair Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfStringStringKeyValuePairLibrary::HasValue(const FOptionalArrayOfStringStringKeyValuePair& Optional, TArray<UStringStringKeyValuePair*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UStringStringKeyValuePair*> UOptionalArrayOfStringStringKeyValuePairLibrary::GetOptionalValue(const FOptionalArrayOfStringStringKeyValuePair& Optional, TArray<UStringStringKeyValuePair*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

