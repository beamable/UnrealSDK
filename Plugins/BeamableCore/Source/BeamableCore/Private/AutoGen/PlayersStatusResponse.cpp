
#include "BeamableCore/Public/AutoGen/PlayersStatusResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UPlayersStatusResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UPlayersStatusResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UOnlineStatus*>, UOnlineStatus*>(TEXT("playersStatus"), &PlayersStatus, Serializer);
}

void UPlayersStatusResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UOnlineStatus*>, UOnlineStatus*>(TEXT("playersStatus"), &PlayersStatus, Serializer);		
}

void UPlayersStatusResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UOnlineStatus*>, UOnlineStatus*>("playersStatus", Bag, PlayersStatus, OuterOwner);
}



