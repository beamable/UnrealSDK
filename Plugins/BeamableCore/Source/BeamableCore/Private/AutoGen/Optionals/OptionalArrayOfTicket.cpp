
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfTicket.h"

FOptionalArrayOfTicket::FOptionalArrayOfTicket()
{
	Val = TArray<UTicket*>();
	IsSet = false;
}

FOptionalArrayOfTicket::FOptionalArrayOfTicket(TArray<UTicket*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfTicket::GetAddr() const { return &Val; }

void FOptionalArrayOfTicket::Set(const void* Data)
{
	Val = *((TArray<UTicket*>*)Data);
	IsSet = true;
}