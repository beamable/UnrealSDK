
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfGroupUsersObjectInFlightMessage.h"

FOptionalArrayOfGroupUsersObjectInFlightMessage::FOptionalArrayOfGroupUsersObjectInFlightMessage()
{
	Val = TArray<UGroupUsersObjectInFlightMessage*>();
	IsSet = false;
}

FOptionalArrayOfGroupUsersObjectInFlightMessage::FOptionalArrayOfGroupUsersObjectInFlightMessage(TArray<UGroupUsersObjectInFlightMessage*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfGroupUsersObjectInFlightMessage::GetAddr() const { return &Val; }

void FOptionalArrayOfGroupUsersObjectInFlightMessage::Set(const void* Data)
{
	Val = *((TArray<UGroupUsersObjectInFlightMessage*>*)Data);
	IsSet = true;
}