
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfPlayerSessionActorPaymentTotal.h"

FOptionalArrayOfPlayerSessionActorPaymentTotal::FOptionalArrayOfPlayerSessionActorPaymentTotal()
{
	Val = TArray<UPlayerSessionActorPaymentTotal*>();
	IsSet = false;
}

FOptionalArrayOfPlayerSessionActorPaymentTotal::FOptionalArrayOfPlayerSessionActorPaymentTotal(TArray<UPlayerSessionActorPaymentTotal*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfPlayerSessionActorPaymentTotal::GetAddr() const { return &Val; }

void FOptionalArrayOfPlayerSessionActorPaymentTotal::Set(const void* Data)
{
	Val = *((TArray<UPlayerSessionActorPaymentTotal*>*)Data);
	IsSet = true;
}