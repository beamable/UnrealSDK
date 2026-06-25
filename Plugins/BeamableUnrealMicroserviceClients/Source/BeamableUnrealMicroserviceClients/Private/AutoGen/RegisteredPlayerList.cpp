
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/RegisteredPlayerList.h"
#include "Serialization/BeamJsonUtils.h"



void URegisteredPlayerList::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void URegisteredPlayerList::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
	UBeamJsonUtils::SerializeArray<URegisteredPlayer*>(TEXT("players"), Players, Serializer);
}

void URegisteredPlayerList::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
	UBeamJsonUtils::SerializeArray<URegisteredPlayer*>(TEXT("players"), Players, Serializer);		
}

void URegisteredPlayerList::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("message"), Bag, Message);
	UBeamJsonUtils::DeserializeArray<URegisteredPlayer*>(TEXT("players"), Bag, Players, OuterOwner);
}



