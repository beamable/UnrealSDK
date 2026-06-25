
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SendPushToSelfRequestArgs.h"





void USendPushToSelfRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("title"), Title, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("body"), Body, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("deepLink"), DeepLink, Serializer);
}

void USendPushToSelfRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("title"), Title, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("body"), Body, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("deepLink"), DeepLink, Serializer);		
}

void USendPushToSelfRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("title"), Bag, Title);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("body"), Bag, Body);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("deepLink"), Bag, DeepLink);
}



