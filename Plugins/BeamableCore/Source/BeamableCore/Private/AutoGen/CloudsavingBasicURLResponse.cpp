
#include "BeamableCore/Public/AutoGen/CloudsavingBasicURLResponse.h"





void UCloudsavingBasicURLResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("url"), Url, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("objectKey"), ObjectKey, Serializer);
}

void UCloudsavingBasicURLResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("url"), Url, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("objectKey"), ObjectKey, Serializer);		
}

void UCloudsavingBasicURLResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("url")), Url);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("objectKey")), ObjectKey);
}



