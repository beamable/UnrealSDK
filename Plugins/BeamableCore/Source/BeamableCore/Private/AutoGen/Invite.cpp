
#include "BeamableCore/Public/AutoGen/Invite.h"
#include "Serialization/BeamJsonUtils.h"




void UInvite::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("playerId"), &PlayerId, Serializer);
	Serializer->WriteValue(TEXT("direction"), UInvitationDirectionLibrary::InvitationDirectionToSerializationName(Direction));
}

void UInvite::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("playerId"), &PlayerId, Serializer);
	Serializer->WriteValue(TEXT("direction"), UInvitationDirectionLibrary::InvitationDirectionToSerializationName(Direction));		
}

void UInvite::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("playerId")), PlayerId, OuterOwner);
	Direction = UInvitationDirectionLibrary::SerializationNameToInvitationDirection(Bag->GetStringField(TEXT("direction")));
}



