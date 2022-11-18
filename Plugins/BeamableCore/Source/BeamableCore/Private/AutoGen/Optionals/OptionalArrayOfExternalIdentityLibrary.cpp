

#include "AutoGen/Optionals/OptionalArrayOfExternalIdentityLibrary.h"

FOptionalArrayOfExternalIdentity UOptionalArrayOfExternalIdentityLibrary::MakeOptional(TArray<UExternalIdentity*> Value)
{
	FOptionalArrayOfExternalIdentity Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfExternalIdentity UOptionalArrayOfExternalIdentityLibrary::Conv_OptionalFromValue(TArray<UExternalIdentity*> Value)
{
	FOptionalArrayOfExternalIdentity Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfExternalIdentityLibrary::HasValue(const FOptionalArrayOfExternalIdentity& Optional, TArray<UExternalIdentity*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UExternalIdentity*> UOptionalArrayOfExternalIdentityLibrary::GetOptionalValue(const FOptionalArrayOfExternalIdentity& Optional, TArray<UExternalIdentity*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

