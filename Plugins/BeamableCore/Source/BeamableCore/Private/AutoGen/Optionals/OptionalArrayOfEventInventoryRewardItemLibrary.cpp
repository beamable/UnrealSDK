

#include "AutoGen/Optionals/OptionalArrayOfEventInventoryRewardItemLibrary.h"

FOptionalArrayOfEventInventoryRewardItem UOptionalArrayOfEventInventoryRewardItemLibrary::MakeOptional(TArray<UEventInventoryRewardItem*> Value)
{
	FOptionalArrayOfEventInventoryRewardItem Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfEventInventoryRewardItem UOptionalArrayOfEventInventoryRewardItemLibrary::Conv_OptionalFromValue(TArray<UEventInventoryRewardItem*> Value)
{
	FOptionalArrayOfEventInventoryRewardItem Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfEventInventoryRewardItemLibrary::HasValue(const FOptionalArrayOfEventInventoryRewardItem& Optional, TArray<UEventInventoryRewardItem*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UEventInventoryRewardItem*> UOptionalArrayOfEventInventoryRewardItemLibrary::GetOptionalValue(const FOptionalArrayOfEventInventoryRewardItem& Optional, TArray<UEventInventoryRewardItem*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

