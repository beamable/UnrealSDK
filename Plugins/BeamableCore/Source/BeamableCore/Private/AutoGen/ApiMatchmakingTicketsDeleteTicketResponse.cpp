
#include "BeamableCore/Public/AutoGen/ApiMatchmakingTicketsDeleteTicketResponse.h"




void UApiMatchmakingTicketsDeleteTicketResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UApiMatchmakingTicketsDeleteTicketResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	
}

void UApiMatchmakingTicketsDeleteTicketResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
			
}

void UApiMatchmakingTicketsDeleteTicketResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	
}



