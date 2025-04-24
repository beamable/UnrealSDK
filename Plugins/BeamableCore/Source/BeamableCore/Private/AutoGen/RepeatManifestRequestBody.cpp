
#include "BeamableCore/Public/AutoGen/RepeatManifestRequestBody.h"





void URepeatManifestRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("uid"), Uid, Serializer);
}

void URepeatManifestRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("uid"), Uid, Serializer);		
}

void URepeatManifestRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("uid")), Uid);
}



