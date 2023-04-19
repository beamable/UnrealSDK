
#include "BeamableCore/Public/AutoGen/RepeatManifestRequestBody.h"





void URepeatManifestRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("uid"), Uid);
}

void URepeatManifestRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("uid"), Uid);		
}

void URepeatManifestRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Uid = Bag->GetStringField(TEXT("uid"));
}



