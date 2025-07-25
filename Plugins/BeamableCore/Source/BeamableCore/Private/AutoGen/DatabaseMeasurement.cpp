
#include "BeamableCore/Public/AutoGen/DatabaseMeasurement.h"
#include "Serialization/BeamJsonUtils.h"




void UDatabaseMeasurement::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("units"), Units, Serializer);
	UBeamJsonUtils::SerializeArray<UDataPoint*>(TEXT("dataPoints"), DataPoints, Serializer);
}

void UDatabaseMeasurement::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("units"), Units, Serializer);
	UBeamJsonUtils::SerializeArray<UDataPoint*>(TEXT("dataPoints"), DataPoints, Serializer);		
}

void UDatabaseMeasurement::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("name"), Bag, Name);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("units"), Bag, Units);
	UBeamJsonUtils::DeserializeArray<UDataPoint*>(TEXT("dataPoints"), Bag, DataPoints, OuterOwner);
}



