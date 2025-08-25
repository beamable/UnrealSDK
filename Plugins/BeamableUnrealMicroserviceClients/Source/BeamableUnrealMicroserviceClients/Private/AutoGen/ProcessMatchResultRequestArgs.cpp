
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/ProcessMatchResultRequestArgs.h"





void UProcessMatchResultRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("winnerId"), WinnerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lobbyId"), LobbyId, Serializer);
}

void UProcessMatchResultRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("winnerId"), WinnerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lobbyId"), LobbyId, Serializer);		
}

void UProcessMatchResultRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("winnerId"), Bag, WinnerId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("lobbyId"), Bag, LobbyId);
}



