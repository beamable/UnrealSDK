
#include "BeamableCore/Public/AutoGen/DatabaseMeasurements.h"
#include "Serialization/BeamJsonUtils.h"




void UDatabaseMeasurements::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("databaseName"), DatabaseName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("granularity"), &Granularity, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("groupId"), &GroupId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("hostId"), &HostId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("processId"), &ProcessId, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("start"), &Start, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("end"), &End, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<ULink*>, ULink*>(TEXT("links"), &Links, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UDatabaseMeasurement*>, UDatabaseMeasurement*>(TEXT("measurements"), &Measurements, Serializer);
}

void UDatabaseMeasurements::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("databaseName"), DatabaseName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("granularity"), &Granularity, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("groupId"), &GroupId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("hostId"), &HostId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("processId"), &ProcessId, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("start"), &Start, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("end"), &End, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<ULink*>, ULink*>(TEXT("links"), &Links, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UDatabaseMeasurement*>, UDatabaseMeasurement*>(TEXT("measurements"), &Measurements, Serializer);		
}

void UDatabaseMeasurements::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("databaseName")), DatabaseName);
	UBeamJsonUtils::DeserializeOptional<FString>("granularity", Bag, Granularity, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("groupId", Bag, GroupId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("hostId", Bag, HostId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("processId", Bag, ProcessId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("start", Bag, Start, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("end", Bag, End, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<ULink*>, ULink*>("links", Bag, Links, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UDatabaseMeasurement*>, UDatabaseMeasurement*>("measurements", Bag, Measurements, OuterOwner);
}



