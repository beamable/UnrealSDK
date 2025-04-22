
#include "BeamableCore/Public/AutoGen/AliasAvailableRequestBody.h"





void UAliasAvailableRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("alias"), Alias, Serializer);
}

void UAliasAvailableRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("alias"), Alias, Serializer);		
}

void UAliasAvailableRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("alias")), Alias);
}



