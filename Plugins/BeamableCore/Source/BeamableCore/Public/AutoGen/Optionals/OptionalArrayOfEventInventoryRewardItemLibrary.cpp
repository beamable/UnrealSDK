

#include "OptionalArrayOfEventInventoryRewardItemLibrary.h"

FOptionalArrayOfEventInventoryRewardItem UOptionalArrayOfEventInventoryRewardItemLibrary::MakeOptionalArrayOfEventInventoryRewardItem(TArray<UEventInventoryRewardItem*> Value)
{
	FOptionalArrayOfEventInventoryRewardItem Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfEventInventoryRewardItem UOptionalArrayOfEventInventoryRewardItemLibrary::Conv_OptionalArrayOfEventInventoryRewardItemFromValue(TArray<UEventInventoryRewardItem*> Value)
{
	FOptionalArrayOfEventInventoryRewardItem Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

