
#include "BeamableCore/Public/AutoGen/EventDateRanges.h"
#include "Serialization/BeamJsonUtils.h"




void UEventDateRanges::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("state"), State, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeArray<UDateRange*>(TEXT("dates"), Dates, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("createdAt"), &CreatedAt, Serializer);
}

void UEventDateRanges::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("state"), State, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeArray<UDateRange*>(TEXT("dates"), Dates, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("createdAt"), &CreatedAt, Serializer);		
}

void UEventDateRanges::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("name"), Bag, Name);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("state"), Bag, State);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("id"), Bag, Id);
	UBeamJsonUtils::DeserializeArray<UDateRange*>(TEXT("dates"), Bag, Dates, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("createdAt", Bag, CreatedAt, OuterOwner);
}



