
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DiscordWhitelistedInfo.h"




void UDiscordWhitelistedInfo::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UDiscordWhitelistedInfo::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("matchmaking_discord_whitelisted"), bMatchmakingDiscordWhitelisted, Serializer);
}

void UDiscordWhitelistedInfo::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("matchmaking_discord_whitelisted"), bMatchmakingDiscordWhitelisted, Serializer);		
}

void UDiscordWhitelistedInfo::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("matchmaking_discord_whitelisted")), bMatchmakingDiscordWhitelisted);
}



