
#include "AutoGen/LeaveRoomResponse.h"



void ULeaveRoomResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("removed"), Removed);
}

void ULeaveRoomResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("removed"), Removed);		
}

void ULeaveRoomResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Removed = Bag->GetStringField(TEXT("removed"));
}