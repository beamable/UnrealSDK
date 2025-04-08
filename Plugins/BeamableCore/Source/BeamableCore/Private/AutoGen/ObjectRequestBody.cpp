
#include "BeamableCore/Public/AutoGen/ObjectRequestBody.h"





void UObjectRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("objectKey"), ObjectKey);
}

void UObjectRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("objectKey"), ObjectKey);		
}

void UObjectRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("objectKey")), ObjectKey);
}



