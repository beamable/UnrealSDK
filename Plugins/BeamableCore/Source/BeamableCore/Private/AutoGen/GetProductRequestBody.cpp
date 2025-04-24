
#include "BeamableCore/Public/AutoGen/GetProductRequestBody.h"





void UGetProductRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sku"), Sku, Serializer);
}

void UGetProductRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sku"), Sku, Serializer);		
}

void UGetProductRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("sku")), Sku);
}



