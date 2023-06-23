
#include "BeamableCore/Public/AutoGen/InviteToParty.h"
#include "Serialization/BeamJsonUtils.h"




void UInviteToParty::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("playerId"), &PlayerId, Serializer);
}

void UInviteToParty::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("playerId"), &PlayerId, Serializer);		
}

void UInviteToParty::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("playerId", Bag, PlayerId, OuterOwner);
}



