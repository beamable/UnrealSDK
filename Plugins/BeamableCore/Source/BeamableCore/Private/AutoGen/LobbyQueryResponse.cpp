
#include "BeamableCore/Public/AutoGen/LobbyQueryResponse.h"
#include "Serialization/BeamJsonUtils.h"



void ULobbyQueryResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void ULobbyQueryResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<ULobby*>, ULobby*>(TEXT("results"), &Results, Serializer);
}

void ULobbyQueryResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<ULobby*>, ULobby*>(TEXT("results"), &Results, Serializer);		
}

void ULobbyQueryResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<ULobby*>, ULobby*>("results", Bag, Results, OuterOwner);
}



