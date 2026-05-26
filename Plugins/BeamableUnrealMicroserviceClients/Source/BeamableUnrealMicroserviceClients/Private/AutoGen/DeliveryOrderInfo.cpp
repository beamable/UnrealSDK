
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DeliveryOrderInfo.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UDeliveryOrderInfo::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("orderId"), OrderId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("displayName"), DisplayName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("requiredItemContentId"), RequiredItemContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("rewardCurrencyId"), RewardCurrencyId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("rewardAmount"), RewardAmount, Serializer);
	UBeamJsonUtils::SerializeArray<UDeliveryRequirement*>(TEXT("requirements"), Requirements, Serializer);
}

void UDeliveryOrderInfo::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("orderId"), OrderId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("displayName"), DisplayName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("requiredItemContentId"), RequiredItemContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("rewardCurrencyId"), RewardCurrencyId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("rewardAmount"), RewardAmount, Serializer);
	UBeamJsonUtils::SerializeArray<UDeliveryRequirement*>(TEXT("requirements"), Requirements, Serializer);		
}

void UDeliveryOrderInfo::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("orderId"), Bag, OrderId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("displayName"), Bag, DisplayName);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("requiredItemContentId"), Bag, RequiredItemContentId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("rewardCurrencyId"), Bag, RewardCurrencyId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("rewardAmount"), Bag, RewardAmount);
	UBeamJsonUtils::DeserializeArray<UDeliveryRequirement*>(TEXT("requirements"), Bag, Requirements, OuterOwner);
}



