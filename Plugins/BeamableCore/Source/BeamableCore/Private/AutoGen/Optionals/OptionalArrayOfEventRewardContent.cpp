
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfEventRewardContent.h"

FOptionalArrayOfEventRewardContent::FOptionalArrayOfEventRewardContent()
{
	Val = TArray<UEventRewardContent*>();
	IsSet = false;
}

FOptionalArrayOfEventRewardContent::FOptionalArrayOfEventRewardContent(TArray<UEventRewardContent*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfEventRewardContent::GetAddr() const { return &Val; }

void FOptionalArrayOfEventRewardContent::Set(const void* Data)
{
	Val = *((TArray<UEventRewardContent*>*)Data);
	IsSet = true;
}