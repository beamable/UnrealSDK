
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DiscordWhitelistedInfo.h"




void UDiscordWhitelistedInfo::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UDiscordWhitelistedInfo::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("matchmaking_discord_whitelisted"), bMatchmakingDiscordWhitelisted);
}

void UDiscordWhitelistedInfo::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("matchmaking_discord_whitelisted"), bMatchmakingDiscordWhitelisted);		
}

void UDiscordWhitelistedInfo::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bMatchmakingDiscordWhitelisted = Bag->GetBoolField(TEXT("matchmaking_discord_whitelisted"));
}



