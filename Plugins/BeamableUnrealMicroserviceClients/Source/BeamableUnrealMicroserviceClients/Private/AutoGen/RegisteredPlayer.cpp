
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/RegisteredPlayer.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void URegisteredPlayer::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("deviceCount"), DeviceCount, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lastUpdated"), LastUpdated, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gamePlatform"), GamePlatform, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gameDevice"), GameDevice, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("platforms"), Platforms, Serializer);
}

void URegisteredPlayer::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("deviceCount"), DeviceCount, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lastUpdated"), LastUpdated, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gamePlatform"), GamePlatform, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gameDevice"), GameDevice, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("platforms"), Platforms, Serializer);		
}

void URegisteredPlayer::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("playerId"), Bag, PlayerId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("deviceCount"), Bag, DeviceCount);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("lastUpdated"), Bag, LastUpdated);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("gamePlatform"), Bag, GamePlatform);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("gameDevice"), Bag, GameDevice);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("platforms"), Bag, Platforms, OuterOwner);
}



