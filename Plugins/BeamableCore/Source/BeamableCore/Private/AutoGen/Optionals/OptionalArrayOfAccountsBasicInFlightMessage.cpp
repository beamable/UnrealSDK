
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfAccountsBasicInFlightMessage.h"

FOptionalArrayOfAccountsBasicInFlightMessage::FOptionalArrayOfAccountsBasicInFlightMessage()
{
	Val = TArray<UAccountsBasicInFlightMessage*>();
	IsSet = false;
}

FOptionalArrayOfAccountsBasicInFlightMessage::FOptionalArrayOfAccountsBasicInFlightMessage(TArray<UAccountsBasicInFlightMessage*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfAccountsBasicInFlightMessage::GetAddr() const { return &Val; }

void FOptionalArrayOfAccountsBasicInFlightMessage::Set(const void* Data)
{
	Val = *((TArray<UAccountsBasicInFlightMessage*>*)Data);
	IsSet = true;
}