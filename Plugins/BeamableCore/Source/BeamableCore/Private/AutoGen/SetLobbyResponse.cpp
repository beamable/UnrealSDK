
#include "BeamableCore/Public/AutoGen/SetLobbyResponse.h"
#include "Serialization/BeamJsonUtils.h"



void USetLobbyResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void USetLobbyResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("lobbyId"), &LobbyId, Serializer);
}

void USetLobbyResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("lobbyId"), &LobbyId, Serializer);		
}

void USetLobbyResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("lobbyId", Bag, LobbyId, OuterOwner);
}



