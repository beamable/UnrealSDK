
#include "AutoGen/FriendshipStatus.h"



void UFriendshipStatus ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	Serializer->WriteValue(TEXT("friendId"), FriendId);
	Serializer->WriteValue(TEXT("isBlocked"), bIsBlocked);
}

void UFriendshipStatus::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	Serializer->WriteValue(TEXT("friendId"), FriendId);
	Serializer->WriteValue(TEXT("isBlocked"), bIsBlocked);		
}

void UFriendshipStatus ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	PlayerId = Bag->GetStringField(TEXT("playerId"));
	FriendId = Bag->GetStringField(TEXT("friendId"));
	bIsBlocked = Bag->GetBoolField(TEXT("isBlocked"));
}