
#include "BeamableCore/Public/AutoGen/CreateRoomRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UCreateRoomRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("keepSubscribed"), bKeepSubscribed);
	Serializer->WriteValue(TEXT("roomName"), RoomName);
	UBeamJsonUtils::SerializeArray<int64>(TEXT("players"), Players, Serializer);
}

void UCreateRoomRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("keepSubscribed"), bKeepSubscribed);
	Serializer->WriteValue(TEXT("roomName"), RoomName);
	UBeamJsonUtils::SerializeArray<int64>(TEXT("players"), Players, Serializer);		
}

void UCreateRoomRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bKeepSubscribed = Bag->GetBoolField(TEXT("keepSubscribed"));
	RoomName = Bag->GetStringField(TEXT("roomName"));
	UBeamJsonUtils::DeserializeArray<int64>(Bag->GetArrayField(TEXT("players")), Players, OuterOwner);
}



