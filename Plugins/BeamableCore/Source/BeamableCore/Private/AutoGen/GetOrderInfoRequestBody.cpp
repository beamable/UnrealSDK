
#include "BeamableCore/Public/AutoGen/GetOrderInfoRequestBody.h"





void UGetOrderInfoRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("orderId"), OrderId);
}

void UGetOrderInfoRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("orderId"), OrderId);		
}

void UGetOrderInfoRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("orderId")), OrderId);
}



