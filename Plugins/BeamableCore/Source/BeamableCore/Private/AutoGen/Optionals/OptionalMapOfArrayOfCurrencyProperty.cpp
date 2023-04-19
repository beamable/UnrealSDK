
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfArrayOfCurrencyProperty.h"

FOptionalMapOfArrayOfCurrencyProperty::FOptionalMapOfArrayOfCurrencyProperty()
{
	Val = TMap<FString, FArrayOfCurrencyProperty>();
	IsSet = false;
}

FOptionalMapOfArrayOfCurrencyProperty::FOptionalMapOfArrayOfCurrencyProperty(TMap<FString, FArrayOfCurrencyProperty> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalMapOfArrayOfCurrencyProperty::GetAddr() const { return &Val; }

void FOptionalMapOfArrayOfCurrencyProperty::Set(const void* Data)
{
	Val = *((TMap<FString, FArrayOfCurrencyProperty>*)Data);
	IsSet = true;
}