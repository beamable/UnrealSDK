
#include "BeamableCore/Public/AutoGen/CancelInviteToParty.h"
#include "Serialization/BeamJsonUtils.h"




void UCancelInviteToParty::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("playerId"), &PlayerId, Serializer);
}

void UCancelInviteToParty::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("playerId"), &PlayerId, Serializer);		
}

void UCancelInviteToParty::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("playerId", Bag, PlayerId, OuterOwner);
}



