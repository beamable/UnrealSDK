
#include "BeamableCore/Public/AutoGen/DatabasePerformanceRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UDatabasePerformanceRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("storageObjectName"), StorageObjectName);
	Serializer->WriteValue(TEXT("granularity"), Granularity);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("endDate"), &EndDate, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("startDate"), &StartDate, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("period"), &Period, Serializer);
}

void UDatabasePerformanceRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("storageObjectName"), StorageObjectName);
	Serializer->WriteValue(TEXT("granularity"), Granularity);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("endDate"), &EndDate, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("startDate"), &StartDate, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("period"), &Period, Serializer);		
}

void UDatabasePerformanceRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	StorageObjectName = Bag->GetStringField(TEXT("storageObjectName"));
	Granularity = Bag->GetStringField(TEXT("granularity"));
	UBeamJsonUtils::DeserializeOptional<FString>("endDate", Bag, EndDate, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("startDate", Bag, StartDate, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("period", Bag, Period, OuterOwner);
}



