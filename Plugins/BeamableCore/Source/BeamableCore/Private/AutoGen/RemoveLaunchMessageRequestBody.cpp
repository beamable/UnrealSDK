
#include "BeamableCore/Public/AutoGen/RemoveLaunchMessageRequestBody.h"





void URemoveLaunchMessageRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("file"), File, Serializer);
}

void URemoveLaunchMessageRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("file"), File, Serializer);		
}

void URemoveLaunchMessageRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("file")), File);
}



