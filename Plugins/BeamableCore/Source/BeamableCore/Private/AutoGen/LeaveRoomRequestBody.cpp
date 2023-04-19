
#include "BeamableCore/Public/AutoGen/LeaveRoomRequestBody.h"





void ULeaveRoomRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("roomId"), RoomId);
}

void ULeaveRoomRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("roomId"), RoomId);		
}

void ULeaveRoomRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	RoomId = Bag->GetStringField(TEXT("roomId"));
}



