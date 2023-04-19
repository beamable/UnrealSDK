
#include "BeamableCore/Public/AutoGen/EventsWithinDateRangeRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UEventsWithinDateRangeRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("from"), &From, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("to"), &To, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("query"), &Query, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);
}

void UEventsWithinDateRangeRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("from"), &From, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("to"), &To, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("query"), &Query, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);		
}

void UEventsWithinDateRangeRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("from", Bag, From, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("to", Bag, To, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("query", Bag, Query, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("limit", Bag, Limit, OuterOwner);
}



