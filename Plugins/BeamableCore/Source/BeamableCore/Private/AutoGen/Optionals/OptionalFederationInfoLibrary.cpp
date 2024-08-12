

#include "AutoGen/Optionals/OptionalFederationInfoLibrary.h"

FOptionalFederationInfo UOptionalFederationInfoLibrary::MakeOptional(UFederationInfo* Value)
{
	FOptionalFederationInfo Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalFederationInfo UOptionalFederationInfoLibrary::Conv_OptionalFromValue(UFederationInfo* Value)
{
	FOptionalFederationInfo Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalFederationInfoLibrary::HasValue(const FOptionalFederationInfo& Optional, UFederationInfo*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UFederationInfo* UOptionalFederationInfoLibrary::GetOptionalValue(const FOptionalFederationInfo& Optional, UFederationInfo* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

