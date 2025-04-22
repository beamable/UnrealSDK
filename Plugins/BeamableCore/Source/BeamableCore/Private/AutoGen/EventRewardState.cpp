
#include "BeamableCore/Public/AutoGen/EventRewardState.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UEventRewardState::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("claimed"), bClaimed, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("earned"), bEarned, Serializer);
	UBeamJsonUtils::SerializeUObject<UEventInventoryPendingRewards*>("pendingInventoryRewards", PendingInventoryRewards, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("min"), Min, Serializer);
	UBeamJsonUtils::SerializeOptional<double>(TEXT("max"), &Max, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UEventInventoryRewardCurrency*>, UEventInventoryRewardCurrency*>(TEXT("currencies"), &Currencies, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UItemCreateRequestBody*>, UItemCreateRequestBody*>(TEXT("pendingItemRewards"), &PendingItemRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UEventInventoryRewardItem*>, UEventInventoryRewardItem*>(TEXT("items"), &Items, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UEventRewardObtain*>, UEventRewardObtain*>(TEXT("obtain"), &Obtain, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("pendingCurrencyRewards"), &PendingCurrencyRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("pendingEntitlementRewards"), &PendingEntitlementRewards, Serializer);
}

void UEventRewardState::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("claimed"), bClaimed, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("earned"), bEarned, Serializer);
	UBeamJsonUtils::SerializeUObject<UEventInventoryPendingRewards*>("pendingInventoryRewards", PendingInventoryRewards, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("min"), Min, Serializer);
	UBeamJsonUtils::SerializeOptional<double>(TEXT("max"), &Max, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UEventInventoryRewardCurrency*>, UEventInventoryRewardCurrency*>(TEXT("currencies"), &Currencies, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UItemCreateRequestBody*>, UItemCreateRequestBody*>(TEXT("pendingItemRewards"), &PendingItemRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UEventInventoryRewardItem*>, UEventInventoryRewardItem*>(TEXT("items"), &Items, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UEventRewardObtain*>, UEventRewardObtain*>(TEXT("obtain"), &Obtain, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("pendingCurrencyRewards"), &PendingCurrencyRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("pendingEntitlementRewards"), &PendingEntitlementRewards, Serializer);		
}

void UEventRewardState::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("claimed")), bClaimed);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("earned")), bEarned);
	UBeamJsonUtils::DeserializeUObject<UEventInventoryPendingRewards*>("pendingInventoryRewards", Bag, PendingInventoryRewards, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("min")), Min);
	UBeamJsonUtils::DeserializeOptional<double>("max", Bag, Max, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UEventInventoryRewardCurrency*>, UEventInventoryRewardCurrency*>("currencies", Bag, Currencies, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UItemCreateRequestBody*>, UItemCreateRequestBody*>("pendingItemRewards", Bag, PendingItemRewards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UEventInventoryRewardItem*>, UEventInventoryRewardItem*>("items", Bag, Items, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UEventRewardObtain*>, UEventRewardObtain*>("obtain", Bag, Obtain, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("pendingCurrencyRewards", Bag, PendingCurrencyRewards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("pendingEntitlementRewards", Bag, PendingEntitlementRewards, OuterOwner);
}



