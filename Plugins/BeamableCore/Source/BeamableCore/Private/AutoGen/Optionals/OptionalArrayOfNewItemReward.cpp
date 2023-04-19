
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfNewItemReward.h"

FOptionalArrayOfNewItemReward::FOptionalArrayOfNewItemReward()
{
	Val = TArray<UNewItemReward*>();
	IsSet = false;
}

FOptionalArrayOfNewItemReward::FOptionalArrayOfNewItemReward(TArray<UNewItemReward*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfNewItemReward::GetAddr() const { return &Val; }

void FOptionalArrayOfNewItemReward::Set(const void* Data)
{
	Val = *((TArray<UNewItemReward*>*)Data);
	IsSet = true;
}