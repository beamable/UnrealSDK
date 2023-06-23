
#include "BeamableCore/Public/AutoGen/PartyInvitation.h"
#include "Serialization/BeamJsonUtils.h"




void UPartyInvitation::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("partyId"), &PartyId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("invitedBy"), &InvitedBy, Serializer);
}

void UPartyInvitation::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("partyId"), &PartyId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("invitedBy"), &InvitedBy, Serializer);		
}

void UPartyInvitation::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("partyId", Bag, PartyId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("invitedBy", Bag, InvitedBy, OuterOwner);
}



