
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
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("playerId")), PlayerId, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UFriend*>(Bag->GetArrayField(TEXT("friends")), Friends, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UPlayerId*>(Bag->GetArrayField(TEXT("blocked")), Blocked, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UInvite*>(Bag->GetArrayField(TEXT("invites")), Invites, OuterOwner);
}



