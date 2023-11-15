

#include "AutoGen/Optionals/OptionalArrayOfBeamExternalIdentityLibrary.h"

FOptionalArrayOfBeamExternalIdentity UOptionalArrayOfBeamExternalIdentityLibrary::MakeOptional(TArray<FBeamExternalIdentity> Value)
{
	FOptionalArrayOfBeamExternalIdentity Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfBeamExternalIdentity UOptionalArrayOfBeamExternalIdentityLibrary::Conv_OptionalFromValue(TArray<FBeamExternalIdentity> Value)
{
	FOptionalArrayOfBeamExternalIdentity Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfBeamExternalIdentityLibrary::HasValue(const FOptionalArrayOfBeamExternalIdentity& Optional, TArray<FBeamExternalIdentity>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<FBeamExternalIdentity> UOptionalArrayOfBeamExternalIdentityLibrary::GetOptionalValue(const FOptionalArrayOfBeamExternalIdentity& Optional, TArray<FBeamExternalIdentity> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

