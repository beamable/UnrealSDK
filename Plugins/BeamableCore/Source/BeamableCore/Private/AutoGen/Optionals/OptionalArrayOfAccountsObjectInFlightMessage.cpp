
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfAccountsObjectInFlightMessage.h"

FOptionalArrayOfAccountsObjectInFlightMessage::FOptionalArrayOfAccountsObjectInFlightMessage()
{
	Val = TArray<UAccountsObjectInFlightMessage*>();
	IsSet = false;
}

FOptionalArrayOfAccountsObjectInFlightMessage::FOptionalArrayOfAccountsObjectInFlightMessage(TArray<UAccountsObjectInFlightMessage*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfAccountsObjectInFlightMessage::GetAddr() const { return &Val; }

void FOptionalArrayOfAccountsObjectInFlightMessage::Set(const void* Data)
{
	Val = *((TArray<UAccountsObjectInFlightMessage*>*)Data);
	IsSet = true;
}