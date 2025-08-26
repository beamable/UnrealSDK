
#include "BeamableCore/Public/AutoGen/StatsSearchResponse.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void UStatsSearchResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UStatsSearchResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("offset"), Offset, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("limit"), Limit, Serializer);
	UBeamJsonUtils::SerializeArray<FBeamGamerTag, int64>(TEXT("ids"), Ids, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("total"), &Total, Serializer);
}

void UStatsSearchResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("offset"), Offset, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("limit"), Limit, Serializer);
	UBeamJsonUtils::SerializeArray<FBeamGamerTag, int64>(TEXT("ids"), Ids, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("total"), &Total, Serializer);		
}

void UStatsSearchResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("offset"), Bag, Offset);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("limit"), Bag, Limit);
	UBeamJsonUtils::DeserializeArray<FBeamGamerTag, int64>(TEXT("ids"), Bag, Ids, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("total", Bag, Total, OuterOwner);
}



