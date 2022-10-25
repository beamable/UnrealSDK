
#include "AutoGen/FriendshipStatus.h"



void UFriendshipStatus ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("isBlocked"), bIsBlocked);
	Serializer->WriteValue(TEXT("friendId"), FriendId);
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
}

void UFriendshipStatus::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("isBlocked"), bIsBlocked);
	Serializer->WriteValue(TEXT("friendId"), FriendId);
	Serializer->WriteValue(TEXT("playerId"), PlayerId);		
}

void UFriendshipStatus ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bIsBlocked = Bag->GetBoolField(TEXT("isBlocked"));
	FriendId = Bag->GetStringField(TEXT("friendId"));
	PlayerId = Bag->GetStringField(TEXT("playerId"));
}