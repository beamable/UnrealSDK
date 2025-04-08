
#include "BeamableCore/Public/AutoGen/RemoveLaunchMessageRequestBody.h"





void URemoveLaunchMessageRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("file"), File);
}

void URemoveLaunchMessageRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("file"), File);		
}

void URemoveLaunchMessageRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("file")), File);
}



