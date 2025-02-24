
#include "BeamableCore/Public/AutoGen/ApiPlayersLobbiesDeletePlayerLobbyResponse.h"




void UApiPlayersLobbiesDeletePlayerLobbyResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UApiPlayersLobbiesDeletePlayerLobbyResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	
}

void UApiPlayersLobbiesDeletePlayerLobbyResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
			
}

void UApiPlayersLobbiesDeletePlayerLobbyResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	
}



