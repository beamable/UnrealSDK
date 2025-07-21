
#include "BeamableCore/Public/AutoGen/BeamoV2DatabaseMeasurements.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoV2DatabaseMeasurements::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("databaseName"), DatabaseName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("granularity"), &Granularity, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("groupId"), &GroupId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("hostId"), &HostId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("processId"), &ProcessId, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("start"), &Start, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("end"), &End, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2Link*>, UBeamoV2Link*>(TEXT("links"), &Links, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2DatabaseMeasurement*>, UBeamoV2DatabaseMeasurement*>(TEXT("measurements"), &Measurements, Serializer);
}

void UBeamoV2DatabaseMeasurements::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("databaseName"), DatabaseName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("granularity"), &Granularity, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("groupId"), &GroupId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("hostId"), &HostId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("processId"), &ProcessId, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("start"), &Start, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("end"), &End, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2Link*>, UBeamoV2Link*>(TEXT("links"), &Links, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2DatabaseMeasurement*>, UBeamoV2DatabaseMeasurement*>(TEXT("measurements"), &Measurements, Serializer);		
}

void UBeamoV2DatabaseMeasurements::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("databaseName")), DatabaseName);
	UBeamJsonUtils::DeserializeOptional<FString>("granularity", Bag, Granularity, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("groupId", Bag, GroupId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("hostId", Bag, HostId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("processId", Bag, ProcessId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("start", Bag, Start, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("end", Bag, End, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UBeamoV2Link*>, UBeamoV2Link*>("links", Bag, Links, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UBeamoV2DatabaseMeasurement*>, UBeamoV2DatabaseMeasurement*>("measurements", Bag, Measurements, OuterOwner);
}



