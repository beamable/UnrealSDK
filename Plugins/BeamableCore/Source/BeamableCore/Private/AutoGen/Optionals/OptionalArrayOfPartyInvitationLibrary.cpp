

#include "AutoGen/Optionals/OptionalArrayOfPartyInvitationLibrary.h"

FOptionalArrayOfPartyInvitation UOptionalArrayOfPartyInvitationLibrary::MakeOptional(TArray<UPartyInvitation*> Value)
{
	FOptionalArrayOfPartyInvitation Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfPartyInvitation UOptionalArrayOfPartyInvitationLibrary::Conv_OptionalFromValue(TArray<UPartyInvitation*> Value)
{
	FOptionalArrayOfPartyInvitation Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfPartyInvitationLibrary::HasValue(const FOptionalArrayOfPartyInvitation& Optional, TArray<UPartyInvitation*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UPartyInvitation*> UOptionalArrayOfPartyInvitationLibrary::GetOptionalValue(const FOptionalArrayOfPartyInvitation& Optional, TArray<UPartyInvitation*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

