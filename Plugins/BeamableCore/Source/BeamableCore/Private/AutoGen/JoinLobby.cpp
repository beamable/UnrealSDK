
#include "BeamableCore/Public/AutoGen/JoinLobby.h"
#include "Serialization/BeamJsonUtils.h"




void UJoinLobby::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UTag*>, UTag*>(TEXT("tags"), &Tags, Serializer);
}

void UJoinLobby::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UTag*>, UTag*>(TEXT("tags"), &Tags, Serializer);		
}

void UJoinLobby::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UTag*>, UTag*>("tags", Bag, Tags, OuterOwner);
}



