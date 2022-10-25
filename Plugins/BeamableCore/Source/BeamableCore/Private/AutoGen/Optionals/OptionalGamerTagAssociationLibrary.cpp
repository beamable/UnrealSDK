

#include "AutoGen/Optionals/OptionalGamerTagAssociationLibrary.h"

FOptionalGamerTagAssociation UOptionalGamerTagAssociationLibrary::MakeOptional(UGamerTagAssociation* Value)
{
	FOptionalGamerTagAssociation Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalGamerTagAssociation UOptionalGamerTagAssociationLibrary::Conv_OptionalFromValue(UGamerTagAssociation* Value)
{
	FOptionalGamerTagAssociation Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalGamerTagAssociationLibrary::HasValue(const FOptionalGamerTagAssociation& Optional, UGamerTagAssociation*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UGamerTagAssociation* UOptionalGamerTagAssociationLibrary::GetOptionalValue(const FOptionalGamerTagAssociation& Optional, UGamerTagAssociation* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

