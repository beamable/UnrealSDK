

#include "AutoGen/Optionals/OptionalBeamExternalIdentityLibrary.h"

FOptionalBeamExternalIdentity UOptionalBeamExternalIdentityLibrary::MakeOptional(FBeamExternalIdentity Value)
{
	FOptionalBeamExternalIdentity Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalBeamExternalIdentity UOptionalBeamExternalIdentityLibrary::Conv_OptionalFromValue(FBeamExternalIdentity Value)
{
	FOptionalBeamExternalIdentity Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalBeamExternalIdentityLibrary::HasValue(const FOptionalBeamExternalIdentity& Optional, FBeamExternalIdentity& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

FBeamExternalIdentity UOptionalBeamExternalIdentityLibrary::GetOptionalValue(const FOptionalBeamExternalIdentity& Optional, FBeamExternalIdentity DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

