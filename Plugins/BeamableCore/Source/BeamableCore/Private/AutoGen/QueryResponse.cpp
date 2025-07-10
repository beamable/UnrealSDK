
#include "BeamableCore/Public/AutoGen/QueryResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UQueryResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UQueryResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("queryId"), &QueryId, Serializer);
}

void UQueryResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("queryId"), &QueryId, Serializer);		
}

void UQueryResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("queryId", Bag, QueryId, OuterOwner);
}



