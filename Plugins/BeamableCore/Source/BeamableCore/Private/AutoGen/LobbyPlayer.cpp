
#include "BeamableCore/Public/AutoGen/LobbyPlayer.h"
#include "Serialization/BeamJsonUtils.h"




void ULobbyPlayer::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("playerId"), &PlayerId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("joined"), &Joined, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UTag*>, UTag*>(TEXT("tags"), &Tags, Serializer);
}

void ULobbyPlayer::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("playerId"), &PlayerId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("joined"), &Joined, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UTag*>, UTag*>(TEXT("tags"), &Tags, Serializer);		
}

void ULobbyPlayer::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("playerId", Bag, PlayerId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("joined", Bag, Joined, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UTag*>, UTag*>("tags", Bag, Tags, OuterOwner);
}



