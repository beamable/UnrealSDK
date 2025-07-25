
#include "BeamableCore/Public/AutoGen/BeamoV2DatabaseMeasurement.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoV2DatabaseMeasurement::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("units"), Units, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2DataPoint*>, UBeamoV2DataPoint*>(TEXT("dataPoints"), &DataPoints, Serializer);
}

void UBeamoV2DatabaseMeasurement::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("units"), Units, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2DataPoint*>, UBeamoV2DataPoint*>(TEXT("dataPoints"), &DataPoints, Serializer);		
}

void UBeamoV2DatabaseMeasurement::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("name")), Name);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("units")), Units);
	UBeamJsonUtils::DeserializeOptional<TArray<UBeamoV2DataPoint*>, UBeamoV2DataPoint*>("dataPoints", Bag, DataPoints, OuterOwner);
}



