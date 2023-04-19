
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfEventRewardObtain.h"

FOptionalArrayOfEventRewardObtain::FOptionalArrayOfEventRewardObtain()
{
	Val = TArray<UEventRewardObtain*>();
	IsSet = false;
}

FOptionalArrayOfEventRewardObtain::FOptionalArrayOfEventRewardObtain(TArray<UEventRewardObtain*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfEventRewardObtain::GetAddr() const { return &Val; }

void FOptionalArrayOfEventRewardObtain::Set(const void* Data)
{
	Val = *((TArray<UEventRewardObtain*>*)Data);
	IsSet = true;
}