
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfPartyInvitation.h"

FOptionalArrayOfPartyInvitation::FOptionalArrayOfPartyInvitation()
{
	Val = TArray<UPartyInvitation*>();
	IsSet = false;
}

FOptionalArrayOfPartyInvitation::FOptionalArrayOfPartyInvitation(TArray<UPartyInvitation*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfPartyInvitation::GetAddr() const { return &Val; }

void FOptionalArrayOfPartyInvitation::Set(const void* Data)
{
	Val = *((TArray<UPartyInvitation*>*)Data);
	IsSet = true;
}