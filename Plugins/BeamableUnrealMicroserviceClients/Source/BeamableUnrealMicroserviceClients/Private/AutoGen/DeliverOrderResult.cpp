
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DeliverOrderResult.h"

#include "Misc/DefaultValueHelper.h"


void UDeliverOrderResult::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UDeliverOrderResult::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("orderId"), OrderId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("rewardCurrencyId"), RewardCurrencyId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("rewardAmount"), RewardAmount, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("success"), bSuccess, Serializer);
}

void UDeliverOrderResult::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("orderId"), OrderId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("rewardCurrencyId"), RewardCurrencyId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("rewardAmount"), RewardAmount, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("success"), bSuccess, Serializer);		
}

void UDeliverOrderResult::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("orderId"), Bag, OrderId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("rewardCurrencyId"), Bag, RewardCurrencyId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("rewardAmount"), Bag, RewardAmount);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("message"), Bag, Message);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("success"), Bag, bSuccess);
}



