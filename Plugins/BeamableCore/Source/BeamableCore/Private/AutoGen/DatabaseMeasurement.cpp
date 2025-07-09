
#include "BeamableCore/Public/AutoGen/DatabaseMeasurement.h"
#include "Serialization/BeamJsonUtils.h"




void UDatabaseMeasurement::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("units"), Units, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoActorDataPoint*>, UBeamoActorDataPoint*>(TEXT("dataPoints"), &DataPoints, Serializer);
}

void UDatabaseMeasurement::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("units"), Units, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoActorDataPoint*>, UBeamoActorDataPoint*>(TEXT("dataPoints"), &DataPoints, Serializer);		
}

void UDatabaseMeasurement::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("name")), Name);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("units")), Units);
	UBeamJsonUtils::DeserializeOptional<TArray<UBeamoActorDataPoint*>, UBeamoActorDataPoint*>("dataPoints", Bag, DataPoints, OuterOwner);
}



