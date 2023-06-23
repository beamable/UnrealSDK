
#include "BeamableCore/Public/AutoGen/TicketReservationResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UTicketReservationResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UTicketReservationResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UTicket*>, UTicket*>(TEXT("tickets"), &Tickets, Serializer);
}

void UTicketReservationResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UTicket*>, UTicket*>(TEXT("tickets"), &Tickets, Serializer);		
}

void UTicketReservationResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UTicket*>, UTicket*>("tickets", Bag, Tickets, OuterOwner);
}



