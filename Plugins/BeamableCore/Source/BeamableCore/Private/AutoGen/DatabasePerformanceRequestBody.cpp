
#include "BeamableCore/Public/AutoGen/DatabasePerformanceRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UDatabasePerformanceRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("storageObjectName"), StorageObjectName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("granularity"), Granularity, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("endDate"), &EndDate, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("startDate"), &StartDate, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("period"), &Period, Serializer);
}

void UDatabasePerformanceRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("storageObjectName"), StorageObjectName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("granularity"), Granularity, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("endDate"), &EndDate, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("startDate"), &StartDate, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("period"), &Period, Serializer);		
}

void UDatabasePerformanceRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("storageObjectName")), StorageObjectName);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("granularity")), Granularity);
	UBeamJsonUtils::DeserializeOptional<FString>("endDate", Bag, EndDate, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("startDate", Bag, StartDate, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("period", Bag, Period, OuterOwner);
}



