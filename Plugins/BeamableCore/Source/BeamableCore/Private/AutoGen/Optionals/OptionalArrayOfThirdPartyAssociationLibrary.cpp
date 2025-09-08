

#include "AutoGen/Optionals/OptionalArrayOfThirdPartyAssociationLibrary.h"

FOptionalArrayOfThirdPartyAssociation UOptionalArrayOfThirdPartyAssociationLibrary::MakeOptional(TArray<UThirdPartyAssociation*> Value)
{
	FOptionalArrayOfThirdPartyAssociation Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfThirdPartyAssociation UOptionalArrayOfThirdPartyAssociationLibrary::Conv_OptionalFromValue(TArray<UThirdPartyAssociation*> Value)
{
	FOptionalArrayOfThirdPartyAssociation Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfThirdPartyAssociationLibrary::HasValue(const FOptionalArrayOfThirdPartyAssociation& Optional, TArray<UThirdPartyAssociation*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UThirdPartyAssociation*> UOptionalArrayOfThirdPartyAssociationLibrary::GetOptionalValue(const FOptionalArrayOfThirdPartyAssociation& Optional, TArray<UThirdPartyAssociation*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

