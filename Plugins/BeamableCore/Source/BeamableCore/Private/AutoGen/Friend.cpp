
#include "AutoGen/Friend.h"



void UFriend ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	Serializer->WriteValue(TEXT("source"), UFriendSourceLibrary::FriendSourceToSerializationName(Source));
}

void UFriend::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	Serializer->WriteValue(TEXT("source"), UFriendSourceLibrary::FriendSourceToSerializationName(Source));		
}

void UFriend ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	PlayerId = Bag->GetStringField(TEXT("playerId"));
	Source = UFriendSourceLibrary::SerializationNameToFriendSource(Bag->GetStringField(TEXT("source")));
}