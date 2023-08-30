
#include "BeamableCore/Public/AutoGen/PartyInvitesForPlayerResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UPartyInvitesForPlayerResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UPartyInvitesForPlayerResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UPartyInvitation*>, UPartyInvitation*>(TEXT("invitations"), &Invitations, Serializer);
}

void UPartyInvitesForPlayerResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UPartyInvitation*>, UPartyInvitation*>(TEXT("invitations"), &Invitations, Serializer);		
}

void UPartyInvitesForPlayerResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UPartyInvitation*>, UPartyInvitation*>("invitations", Bag, Invitations, OuterOwner);
}



