
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CreateMatchResultRequestArgs.h"

#include "Misc/DefaultValueHelper.h"



void UCreateMatchResultRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("userId"), UserId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lobbyId"), LobbyId, Serializer);
}

void UCreateMatchResultRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("userId"), UserId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lobbyId"), LobbyId, Serializer);		
}

void UCreateMatchResultRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("userId")), UserId);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("lobbyId")), LobbyId);
}



