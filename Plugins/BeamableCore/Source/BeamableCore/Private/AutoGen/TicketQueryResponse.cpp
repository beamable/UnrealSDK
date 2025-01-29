
#include "BeamableCore/Public/AutoGen/TicketQueryResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UTicketQueryResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UTicketQueryResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UTicket*>, UTicket*>(TEXT("results"), &Results, Serializer);
}

void UTicketQueryResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UTicket*>, UTicket*>(TEXT("results"), &Results, Serializer);		
}

void UTicketQueryResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UTicket*>, UTicket*>("results", Bag, Results, OuterOwner);
}



