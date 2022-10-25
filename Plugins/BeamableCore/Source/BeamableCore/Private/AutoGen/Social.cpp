
#include "AutoGen/Social.h"
#include "Serialization/BeamJsonUtils.h"


void USocial ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	UBeamJsonUtils::SerializeArray<UFriend*>(TEXT("friends"), Friends, Serializer);
	UBeamJsonUtils::SerializeArray<UPlayerId*>(TEXT("blocked"), Blocked, Serializer);
	UBeamJsonUtils::SerializeArray<UInvite*>(TEXT("invites"), Invites, Serializer);
}

void USocial::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	UBeamJsonUtils::SerializeArray<UFriend*>(TEXT("friends"), Friends, Serializer);
	UBeamJsonUtils::SerializeArray<UPlayerId*>(TEXT("blocked"), Blocked, Serializer);
	UBeamJsonUtils::SerializeArray<UInvite*>(TEXT("invites"), Invites, Serializer);		
}

void USocial ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	PlayerId = Bag->GetStringField(TEXT("playerId"));
	UBeamJsonUtils::DeserializeArray<UFriend*>(Bag->GetArrayField(TEXT("friends")), Friends, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UPlayerId*>(Bag->GetArrayField(TEXT("blocked")), Blocked, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UInvite*>(Bag->GetArrayField(TEXT("invites")), Invites, OuterOwner);
}