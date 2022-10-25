
#include "AutoGen/EventsInDateRangeResponse.h"
#include "Serialization/BeamJsonUtils.h"


void UEventsInDateRangeResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UEventDateRanges*>(TEXT("eventInDateRange"), EventInDateRange, Serializer);
}

void UEventsInDateRangeResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UEventDateRanges*>(TEXT("eventInDateRange"), EventInDateRange, Serializer);		
}

void UEventsInDateRangeResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UEventDateRanges*>(Bag->GetArrayField(TEXT("eventInDateRange")), EventInDateRange, OuterOwner);
}