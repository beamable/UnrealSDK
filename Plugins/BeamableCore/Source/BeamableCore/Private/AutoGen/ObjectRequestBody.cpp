
#include "BeamableCore/Public/AutoGen/ObjectRequestBody.h"





void UObjectRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("objectKey"), ObjectKey, Serializer);
}

void UObjectRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("objectKey"), ObjectKey, Serializer);		
}

void UObjectRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("objectKey")), ObjectKey);
}



