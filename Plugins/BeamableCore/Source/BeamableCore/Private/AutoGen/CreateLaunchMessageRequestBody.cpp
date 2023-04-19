
#include "BeamableCore/Public/AutoGen/CreateLaunchMessageRequestBody.h"





void UCreateLaunchMessageRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("body"), Body);
}

void UCreateLaunchMessageRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("body"), Body);		
}

void UCreateLaunchMessageRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	Body = Bag->GetStringField(TEXT("body"));
}



