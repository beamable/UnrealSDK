
#include "BeamableCore/Public/AutoGen/Social.h"
#include "Serialization/BeamJsonUtils.h"



void USocial::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void USocial::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("playerId"), &PlayerId, Serializer);
	UBeamJsonUtils::SerializeArray<UFriend*>(TEXT("friends"), Friends, Serializer);
	UBeamJsonUtils::SerializeArray<UPlayerId*>(TEXT("blocked"), Blocked, Serializer);
	UBeamJsonUtils::SerializeArray<UInvite*>(TEXT("invites"), Invites, Serializer);
}

void USocial::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("playerId"), &PlayerId, Serializer);
	UBeamJsonUtils::SerializeArray<UFriend*>(TEXT("friends"), Friends, Serializer);
	UBeamJsonUtils::SerializeArray<UPlayerId*>(TEXT("blocked"), Blocked, Serializer);
	UBeamJsonUtils::SerializeArray<UInvite*>(TEXT("invites"), Invites, Serializer);		
}

void USocial::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(TEXT("playerId"), Bag, PlayerId, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UFriend*>(TEXT("friends"), Bag, Friends, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UPlayerId*>(TEXT("blocked"), Bag, Blocked, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UInvite*>(TEXT("invites"), Bag, Invites, OuterOwner);
}



