
#include "AutoGen/DatabasePerformanceRequestBody.h"
#include "Serialization/BeamJsonUtils.h"


void UDatabasePerformanceRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("endDate"), &EndDate, Serializer);
	Serializer->WriteValue(TEXT("storageObjectName"), StorageObjectName);
	Serializer->WriteValue(TEXT("granularity"), Granularity);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("startDate"), &StartDate, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("period"), &Period, Serializer);
}

void UDatabasePerformanceRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("endDate"), &EndDate, Serializer);
	Serializer->WriteValue(TEXT("storageObjectName"), StorageObjectName);
	Serializer->WriteValue(TEXT("granularity"), Granularity);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("startDate"), &StartDate, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("period"), &Period, Serializer);		
}

void UDatabasePerformanceRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("endDate", Bag, EndDate, OuterOwner);
	StorageObjectName = Bag->GetStringField(TEXT("storageObjectName"));
	Granularity = Bag->GetStringField(TEXT("granularity"));
	UBeamJsonUtils::DeserializeOptional<FString>("startDate", Bag, StartDate, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("period", Bag, Period, OuterOwner);
}