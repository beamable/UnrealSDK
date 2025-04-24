
#include "BeamableCore/Public/AutoGen/UploadURL.h"





void UUploadURL::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("key"), Key, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("url"), Url, Serializer);
}

void UUploadURL::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("key"), Key, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("url"), Url, Serializer);		
}

void UUploadURL::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("key")), Key);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("url")), Url);
}



