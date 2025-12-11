
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfTransaction.h"

FOptionalArrayOfTransaction::FOptionalArrayOfTransaction()
{
	Val = TArray<UTransaction*>();
	IsSet = false;
}

FOptionalArrayOfTransaction::FOptionalArrayOfTransaction(TArray<UTransaction*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfTransaction::GetAddr() const { return &Val; }

void FOptionalArrayOfTransaction::Set(const void* Data)
{
	Val = *((TArray<UTransaction*>*)Data);
	IsSet = true;
}