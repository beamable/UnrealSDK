
#include "AutoGen/GetRoomsResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGetRoomsResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetRoomsResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<URoomInfo*>(TEXT("rooms"), Rooms, Serializer);
}

void UGetRoomsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<URoomInfo*>(TEXT("rooms"), Rooms, Serializer);		
}

void UGetRoomsResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<URoomInfo*>(Bag->GetArrayField(TEXT("rooms")), Rooms, OuterOwner);
}



