
#include "BeamableCore/Public/AutoGen/StatsSearchResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UStatsSearchResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UStatsSearchResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FBeamGamerTag, int64>(TEXT("ids"), Ids, Serializer);
}

void UStatsSearchResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FBeamGamerTag, int64>(TEXT("ids"), Ids, Serializer);		
}

void UStatsSearchResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<FBeamGamerTag, int64>(Bag->GetArrayField(TEXT("ids")), Ids, OuterOwner);
}



