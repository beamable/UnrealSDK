
#include "BeamableCore/Public/AutoGen/SetCustomerAliasRequestBody.h"





void USetCustomerAliasRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("alias"), Alias, Serializer);
}

void USetCustomerAliasRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("alias"), Alias, Serializer);		
}

void USetCustomerAliasRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("alias"), Bag, Alias);
}



