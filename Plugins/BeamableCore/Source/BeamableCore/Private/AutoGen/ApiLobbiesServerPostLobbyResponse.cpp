
#include "BeamableCore/Public/AutoGen/ApiLobbiesServerPostLobbyResponse.h"




void UApiLobbiesServerPostLobbyResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UApiLobbiesServerPostLobbyResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	
}

void UApiLobbiesServerPostLobbyResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
			
}

void UApiLobbiesServerPostLobbyResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	
}



