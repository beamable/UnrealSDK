
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/ProcessMatchResultRequestArgs.h"
#include "Serialization/BeamJsonUtils.h"




void UProcessMatchResultRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lobbyId"), LobbyId, Serializer);
	UBeamJsonUtils::SerializeArray<UBeamballTeamInfo*>(TEXT("teamInfos"), TeamInfos, Serializer);
}

void UProcessMatchResultRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lobbyId"), LobbyId, Serializer);
	UBeamJsonUtils::SerializeArray<UBeamballTeamInfo*>(TEXT("teamInfos"), TeamInfos, Serializer);		
}

void UProcessMatchResultRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("lobbyId"), Bag, LobbyId);
	UBeamJsonUtils::DeserializeArray<UBeamballTeamInfo*>(TEXT("teamInfos"), Bag, TeamInfos, OuterOwner);
}



