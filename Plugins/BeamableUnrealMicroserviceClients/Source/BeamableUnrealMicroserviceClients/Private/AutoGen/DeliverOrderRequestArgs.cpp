
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DeliverOrderRequestArgs.h"

#include "Misc/DefaultValueHelper.h"



void UDeliverOrderRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("orderId"), OrderId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemInstanceId"), ItemInstanceId, Serializer);
}

void UDeliverOrderRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("orderId"), OrderId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemInstanceId"), ItemInstanceId, Serializer);		
}

void UDeliverOrderRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("orderId"), Bag, OrderId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("itemInstanceId"), Bag, ItemInstanceId);
}



