

#include "OptionalGamerTagAssociationLibrary.h"

FOptionalGamerTagAssociation UOptionalGamerTagAssociationLibrary::MakeOptionalGamerTagAssociation(UGamerTagAssociation* Value)
{
	FOptionalGamerTagAssociation Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalGamerTagAssociation UOptionalGamerTagAssociationLibrary::Conv_OptionalGamerTagAssociationFromValue(UGamerTagAssociation* Value)
{
	FOptionalGamerTagAssociation Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

