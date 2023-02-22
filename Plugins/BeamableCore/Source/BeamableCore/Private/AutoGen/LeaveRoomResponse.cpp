
#include "AutoGen/LeaveRoomResponse.h"




void ULeaveRoomResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void ULeaveRoomResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("removed"), Removed);
}

void ULeaveRoomResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("removed"), Removed);		
}

void ULeaveRoomResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Removed = Bag->GetStringField(TEXT("removed"));
}



