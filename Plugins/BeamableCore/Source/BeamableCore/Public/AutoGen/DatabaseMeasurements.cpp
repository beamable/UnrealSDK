
#include "AutoGen/DatabaseMeasurements.h"
#include "Serialization/BeamJsonUtils.h"


void UDatabaseMeasurements ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UDatabaseMeasurement*>, UDatabaseMeasurement*>(TEXT("measurements"), &Measurements, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("groupId"), &GroupId, Serializer);
	UBeamJsonUtils::SerializeArray<ULink*>(TEXT("links"), Links, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("hostId"), &HostId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("granularity"), &Granularity, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("end"), &End, Serializer);
	Serializer->WriteValue(TEXT("databaseName"), DatabaseName);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("start"), &Start, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("processId"), &ProcessId, Serializer);
}

void UDatabaseMeasurements::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UDatabaseMeasurement*>, UDatabaseMeasurement*>(TEXT("measurements"), &Measurements, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("groupId"), &GroupId, Serializer);
	UBeamJsonUtils::SerializeArray<ULink*>(TEXT("links"), Links, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("hostId"), &HostId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("granularity"), &Granularity, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("end"), &End, Serializer);
	Serializer->WriteValue(TEXT("databaseName"), DatabaseName);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("start"), &Start, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("processId"), &ProcessId, Serializer);		
}

void UDatabaseMeasurements ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UDatabaseMeasurement*>, UDatabaseMeasurement*>("measurements", Bag, Measurements, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("groupId", Bag, GroupId, OuterOwner);
	UBeamJsonUtils::DeserializeArray<ULink*>(Bag->GetArrayField(TEXT("links")), Links, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("hostId", Bag, HostId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("granularity", Bag, Granularity, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("end", Bag, End, OuterOwner);
	DatabaseName = Bag->GetStringField(TEXT("databaseName"));
	UBeamJsonUtils::DeserializeOptional<FString>("start", Bag, Start, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("processId", Bag, ProcessId, OuterOwner);
}