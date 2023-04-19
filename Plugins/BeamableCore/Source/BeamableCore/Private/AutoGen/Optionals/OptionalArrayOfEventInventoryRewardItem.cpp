
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfEventInventoryRewardItem.h"

FOptionalArrayOfEventInventoryRewardItem::FOptionalArrayOfEventInventoryRewardItem()
{
	Val = TArray<UEventInventoryRewardItem*>();
	IsSet = false;
}

FOptionalArrayOfEventInventoryRewardItem::FOptionalArrayOfEventInventoryRewardItem(TArray<UEventInventoryRewardItem*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfEventInventoryRewardItem::GetAddr() const { return &Val; }

void FOptionalArrayOfEventInventoryRewardItem::Set(const void* Data)
{
	Val = *((TArray<UEventInventoryRewardItem*>*)Data);
	IsSet = true;
}