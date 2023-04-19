
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfCurrencyChange.h"

FOptionalArrayOfCurrencyChange::FOptionalArrayOfCurrencyChange()
{
	Val = TArray<UCurrencyChange*>();
	IsSet = false;
}

FOptionalArrayOfCurrencyChange::FOptionalArrayOfCurrencyChange(TArray<UCurrencyChange*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfCurrencyChange::GetAddr() const { return &Val; }

void FOptionalArrayOfCurrencyChange::Set(const void* Data)
{
	Val = *((TArray<UCurrencyChange*>*)Data);
	IsSet = true;
}