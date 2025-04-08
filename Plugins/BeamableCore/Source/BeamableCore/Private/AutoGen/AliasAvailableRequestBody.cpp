
#include "BeamableCore/Public/AutoGen/AliasAvailableRequestBody.h"





void UAliasAvailableRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("alias"), Alias);
}

void UAliasAvailableRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("alias"), Alias);		
}

void UAliasAvailableRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("alias")), Alias);
}



