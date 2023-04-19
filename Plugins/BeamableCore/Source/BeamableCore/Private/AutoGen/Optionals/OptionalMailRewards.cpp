
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMailRewards.h"

FOptionalMailRewards::FOptionalMailRewards()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalMailRewards::FOptionalMailRewards(UMailRewards* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalMailRewards::GetAddr() const { return &Val; }

void FOptionalMailRewards::Set(const void* Data)
{
	Val = *((UMailRewards**)Data);
	IsSet = true;
}