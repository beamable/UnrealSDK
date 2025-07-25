
#include "BeamableCore/Public/AutoGen/StatsResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UStatsResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UStatsResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("stats"), Stats, Serializer);
}

void UStatsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("stats"), Stats, Serializer);		
}

void UStatsResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<int64>(TEXT("id"), Bag, Id, OuterOwner);
	UBeamJsonUtils::DeserializeMap<FString>(TEXT("stats"), Bag, Stats, OuterOwner);
}



