
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SendPushToPlayerRequestArgs.h"

#include "Misc/DefaultValueHelper.h"



void USendPushToPlayerRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("title"), Title, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("body"), Body, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("deepLink"), DeepLink, Serializer);
}

void USendPushToPlayerRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("title"), Title, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("body"), Body, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("deepLink"), DeepLink, Serializer);		
}

void USendPushToPlayerRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("playerId"), Bag, PlayerId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("title"), Bag, Title);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("body"), Bag, Body);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("deepLink"), Bag, DeepLink);
}



