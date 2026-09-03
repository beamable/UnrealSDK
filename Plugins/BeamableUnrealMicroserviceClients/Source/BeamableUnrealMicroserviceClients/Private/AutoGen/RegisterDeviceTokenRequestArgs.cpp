
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/RegisterDeviceTokenRequestArgs.h"





void URegisterDeviceTokenRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("token"), Token, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("environment"), Environment, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("platform"), Platform, Serializer);
}

void URegisterDeviceTokenRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("token"), Token, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("environment"), Environment, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("platform"), Platform, Serializer);		
}

void URegisterDeviceTokenRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("token"), Bag, Token);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("environment"), Bag, Environment);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("platform"), Bag, Platform);
}



