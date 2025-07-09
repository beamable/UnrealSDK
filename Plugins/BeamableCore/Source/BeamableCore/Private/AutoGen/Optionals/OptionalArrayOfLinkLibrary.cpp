

#include "AutoGen/Optionals/OptionalArrayOfLinkLibrary.h"

FOptionalArrayOfLink UOptionalArrayOfLinkLibrary::MakeOptional(TArray<ULink*> Value)
{
	FOptionalArrayOfLink Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfLink UOptionalArrayOfLinkLibrary::Conv_OptionalFromValue(TArray<ULink*> Value)
{
	FOptionalArrayOfLink Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfLinkLibrary::HasValue(const FOptionalArrayOfLink& Optional, TArray<ULink*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<ULink*> UOptionalArrayOfLinkLibrary::GetOptionalValue(const FOptionalArrayOfLink& Optional, TArray<ULink*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

