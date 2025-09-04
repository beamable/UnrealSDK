
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
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("offset"), &Offset, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("total"), &Total, Serializer);
}

void UStatsSearchResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FBeamGamerTag, int64>(TEXT("ids"), Ids, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("offset"), &Offset, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("total"), &Total, Serializer);		
}

void UStatsSearchResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<FBeamGamerTag, int64>(TEXT("ids"), Bag, Ids, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("offset", Bag, Offset, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("limit", Bag, Limit, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("total", Bag, Total, OuterOwner);
}



