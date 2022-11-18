
#include "AutoGen/CreateRoomResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UCreateRoomResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UCreateRoomResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<URoomInfo*>("room", Room, Serializer);
}

void UCreateRoomResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<URoomInfo*>("room", Room, Serializer);		
}

void UCreateRoomResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<URoomInfo*>("room", Bag, Room, OuterOwner);
}