
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DeviceInfo.h"

#include "Misc/DefaultValueHelper.h"



void UDeviceInfo::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("token"), Token, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("platform"), Platform, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("environment"), Environment, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("updatedAt"), UpdatedAt, Serializer);
}

void UDeviceInfo::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("token"), Token, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("platform"), Platform, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("environment"), Environment, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("updatedAt"), UpdatedAt, Serializer);		
}

void UDeviceInfo::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("token"), Bag, Token);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("platform"), Bag, Platform);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("environment"), Bag, Environment);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("updatedAt"), Bag, UpdatedAt);
}



