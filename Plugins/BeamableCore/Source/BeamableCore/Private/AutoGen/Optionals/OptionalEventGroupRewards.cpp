
#include "BeamableCore/Public/AutoGen/Optionals/OptionalEventGroupRewards.h"

FOptionalEventGroupRewards::FOptionalEventGroupRewards()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalEventGroupRewards::FOptionalEventGroupRewards(UEventGroupRewards* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalEventGroupRewards::GetAddr() const { return &Val; }

void FOptionalEventGroupRewards::Set(const void* Data)
{
	Val = *((UEventGroupRewards**)Data);
	IsSet = true;
}