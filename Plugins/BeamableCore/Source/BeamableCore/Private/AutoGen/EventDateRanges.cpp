
#include "BeamableCore/Public/AutoGen/EventDateRanges.h"
#include "Serialization/BeamJsonUtils.h"




void UEventDateRanges::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("state"), State);
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeArray<UDateRange*>(TEXT("dates"), Dates, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("createdAt"), &CreatedAt, Serializer);
}

void UEventDateRanges::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("state"), State);
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeArray<UDateRange*>(TEXT("dates"), Dates, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("createdAt"), &CreatedAt, Serializer);		
}

void UEventDateRanges::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	State = Bag->GetStringField(TEXT("state"));
	Id = Bag->GetStringField(TEXT("id"));
	UBeamJsonUtils::DeserializeArray<UDateRange*>(Bag->GetArrayField(TEXT("dates")), Dates, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("createdAt", Bag, CreatedAt, OuterOwner);
}



