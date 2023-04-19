
#include "BeamableCore/Public/AutoGen/GetProductRequestBody.h"





void UGetProductRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("sku"), Sku);
}

void UGetProductRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("sku"), Sku);		
}

void UGetProductRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Sku = Bag->GetStringField(TEXT("sku"));
}



