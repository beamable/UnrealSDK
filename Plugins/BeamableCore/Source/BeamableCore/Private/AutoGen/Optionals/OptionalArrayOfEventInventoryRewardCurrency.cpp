
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfEventInventoryRewardCurrency.h"

FOptionalArrayOfEventInventoryRewardCurrency::FOptionalArrayOfEventInventoryRewardCurrency()
{
	Val = TArray<UEventInventoryRewardCurrency*>();
	IsSet = false;
}

FOptionalArrayOfEventInventoryRewardCurrency::FOptionalArrayOfEventInventoryRewardCurrency(TArray<UEventInventoryRewardCurrency*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfEventInventoryRewardCurrency::GetAddr() const { return &Val; }

void FOptionalArrayOfEventInventoryRewardCurrency::Set(const void* Data)
{
	Val = *((TArray<UEventInventoryRewardCurrency*>*)Data);
	IsSet = true;
}