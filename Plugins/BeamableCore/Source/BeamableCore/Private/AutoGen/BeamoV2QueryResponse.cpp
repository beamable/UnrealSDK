
#include "BeamableCore/Public/AutoGen/BeamoV2QueryResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UBeamoV2QueryResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UBeamoV2QueryResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("queryId"), &QueryId, Serializer);
}

void UBeamoV2QueryResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("queryId"), &QueryId, Serializer);		
}

void UBeamoV2QueryResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("queryId", Bag, QueryId, OuterOwner);
}



