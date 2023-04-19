
#include "BeamableCore/Public/AutoGen/BatchReadStatsResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UBatchReadStatsResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UBatchReadStatsResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UNetworkSerializable*>(TEXT("results"), Results, Serializer);
}

void UBatchReadStatsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UNetworkSerializable*>(TEXT("results"), Results, Serializer);		
}

void UBatchReadStatsResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UNetworkSerializable*>(Bag->GetArrayField(TEXT("results")), Results, OuterOwner);
}



