
#include "AutoGen/EventRewardState.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UEventRewardState ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UEventInventoryPendingRewards*>("pendingInventoryRewards", PendingInventoryRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UEventInventoryRewardCurrency*>, UEventInventoryRewardCurrency*>(TEXT("currencies"), &Currencies, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("pendingCurrencyRewards"), &PendingCurrencyRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UItemCreateRequestBody*>, UItemCreateRequestBody*>(TEXT("pendingItemRewards"), &PendingItemRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UEventInventoryRewardItem*>, UEventInventoryRewardItem*>(TEXT("items"), &Items, Serializer);
	Serializer->WriteValue(TEXT("min"), Min);
	UBeamJsonUtils::SerializeOptional<double>(TEXT("max"), &Max, Serializer);
	Serializer->WriteValue(TEXT("earned"), bEarned);
	Serializer->WriteValue(TEXT("claimed"), bClaimed);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("pendingEntitlementRewards"), &PendingEntitlementRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UEventRewardObtain*>, UEventRewardObtain*>(TEXT("obtain"), &Obtain, Serializer);
}

void UEventRewardState::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UEventInventoryPendingRewards*>("pendingInventoryRewards", PendingInventoryRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UEventInventoryRewardCurrency*>, UEventInventoryRewardCurrency*>(TEXT("currencies"), &Currencies, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("pendingCurrencyRewards"), &PendingCurrencyRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UItemCreateRequestBody*>, UItemCreateRequestBody*>(TEXT("pendingItemRewards"), &PendingItemRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UEventInventoryRewardItem*>, UEventInventoryRewardItem*>(TEXT("items"), &Items, Serializer);
	Serializer->WriteValue(TEXT("min"), Min);
	UBeamJsonUtils::SerializeOptional<double>(TEXT("max"), &Max, Serializer);
	Serializer->WriteValue(TEXT("earned"), bEarned);
	Serializer->WriteValue(TEXT("claimed"), bClaimed);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("pendingEntitlementRewards"), &PendingEntitlementRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UEventRewardObtain*>, UEventRewardObtain*>(TEXT("obtain"), &Obtain, Serializer);		
}

void UEventRewardState ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<UEventInventoryPendingRewards*>("pendingInventoryRewards", Bag, PendingInventoryRewards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UEventInventoryRewardCurrency*>, UEventInventoryRewardCurrency*>("currencies", Bag, Currencies, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("pendingCurrencyRewards", Bag, PendingCurrencyRewards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UItemCreateRequestBody*>, UItemCreateRequestBody*>("pendingItemRewards", Bag, PendingItemRewards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UEventInventoryRewardItem*>, UEventInventoryRewardItem*>("items", Bag, Items, OuterOwner);
	Min = Bag->GetNumberField(TEXT("min"));
	UBeamJsonUtils::DeserializeOptional<double>("max", Bag, Max, OuterOwner);
	bEarned = Bag->GetBoolField(TEXT("earned"));
	bClaimed = Bag->GetBoolField(TEXT("claimed"));
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("pendingEntitlementRewards", Bag, PendingEntitlementRewards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UEventRewardObtain*>, UEventRewardObtain*>("obtain", Bag, Obtain, OuterOwner);
}