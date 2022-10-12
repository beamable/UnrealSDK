
#include "AutoGen/CreateRoomRequestBody.h"
#include "Serialization/BeamJsonUtils.h"


void UCreateRoomRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("roomName"), RoomName);
	Serializer->WriteValue(TEXT("keepSubscribed"), bKeepSubscribed);
	UBeamJsonUtils::SerializeArray<int64>(TEXT("players"), Players, Serializer);
}

void UCreateRoomRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("roomName"), RoomName);
	Serializer->WriteValue(TEXT("keepSubscribed"), bKeepSubscribed);
	UBeamJsonUtils::SerializeArray<int64>(TEXT("players"), Players, Serializer);		
}

void UCreateRoomRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	RoomName = Bag->GetStringField(TEXT("roomName"));
	bKeepSubscribed = Bag->GetBoolField(TEXT("keepSubscribed"));
	UBeamJsonUtils::DeserializeArray<int64>(Bag->GetArrayField(TEXT("players")), Players, OuterOwner);
}