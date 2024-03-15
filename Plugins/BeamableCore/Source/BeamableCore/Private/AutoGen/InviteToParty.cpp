
#include "BeamableCore/Public/AutoGen/InviteToParty.h"
#include "Serialization/BeamJsonUtils.h"




void UInviteToParty::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FBeamGamerTag, FString>(TEXT("playerId"), &PlayerId, Serializer);
}

void UInviteToParty::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FBeamGamerTag, FString>(TEXT("playerId"), &PlayerId, Serializer);		
}

void UInviteToParty::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FBeamGamerTag, FString>("playerId", Bag, PlayerId, OuterOwner);
}



