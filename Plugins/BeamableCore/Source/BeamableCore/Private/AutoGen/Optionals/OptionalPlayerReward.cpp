
#include "BeamableCore/Public/AutoGen/Optionals/OptionalPlayerReward.h"

FOptionalPlayerReward::FOptionalPlayerReward()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalPlayerReward::FOptionalPlayerReward(UPlayerReward* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalPlayerReward::GetAddr() const { return &Val; }

void FOptionalPlayerReward::Set(const void* Data)
{
	Val = *((UPlayerReward**)Data);
	IsSet = true;
}