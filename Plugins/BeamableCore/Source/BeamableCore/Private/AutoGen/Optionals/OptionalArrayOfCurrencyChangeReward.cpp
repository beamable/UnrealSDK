
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfCurrencyChangeReward.h"

FOptionalArrayOfCurrencyChangeReward::FOptionalArrayOfCurrencyChangeReward()
{
	Val = TArray<UCurrencyChangeReward*>();
	IsSet = false;
}

FOptionalArrayOfCurrencyChangeReward::FOptionalArrayOfCurrencyChangeReward(TArray<UCurrencyChangeReward*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfCurrencyChangeReward::GetAddr() const { return &Val; }

void FOptionalArrayOfCurrencyChangeReward::Set(const void* Data)
{
	Val = *((TArray<UCurrencyChangeReward*>*)Data);
	IsSet = true;
}