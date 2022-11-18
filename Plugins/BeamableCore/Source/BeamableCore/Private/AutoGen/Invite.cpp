
#include "AutoGen/Invite.h"





void UInvite ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	Serializer->WriteValue(TEXT("direction"), UInvitationDirectionLibrary::InvitationDirectionToSerializationName(Direction));
}

void UInvite::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	Serializer->WriteValue(TEXT("direction"), UInvitationDirectionLibrary::InvitationDirectionToSerializationName(Direction));		
}

void UInvite ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	PlayerId = Bag->GetStringField(TEXT("playerId"));
	Direction = UInvitationDirectionLibrary::SerializationNameToInvitationDirection(Bag->GetStringField(TEXT("direction")));
}