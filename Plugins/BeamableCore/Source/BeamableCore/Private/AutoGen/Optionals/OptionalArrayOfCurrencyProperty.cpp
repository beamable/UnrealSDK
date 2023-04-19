
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfCurrencyProperty.h"

FOptionalArrayOfCurrencyProperty::FOptionalArrayOfCurrencyProperty()
{
	Val = TArray<UCurrencyProperty*>();
	IsSet = false;
}

FOptionalArrayOfCurrencyProperty::FOptionalArrayOfCurrencyProperty(TArray<UCurrencyProperty*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfCurrencyProperty::GetAddr() const { return &Val; }

void FOptionalArrayOfCurrencyProperty::Set(const void* Data)
{
	Val = *((TArray<UCurrencyProperty*>*)Data);
	IsSet = true;
}