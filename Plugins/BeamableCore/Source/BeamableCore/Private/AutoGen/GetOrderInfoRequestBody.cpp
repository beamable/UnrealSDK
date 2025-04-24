
#include "BeamableCore/Public/AutoGen/GetOrderInfoRequestBody.h"





void UGetOrderInfoRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("orderId"), OrderId, Serializer);
}

void UGetOrderInfoRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("orderId"), OrderId, Serializer);		
}

void UGetOrderInfoRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("orderId")), OrderId);
}



