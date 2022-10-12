
#include "AutoGen/DatabaseMeasurement.h"
#include "Serialization/BeamJsonUtils.h"


void UDatabaseMeasurement ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UDataPoint*>(TEXT("dataPoints"), DataPoints, Serializer);
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("units"), Units);
}

void UDatabaseMeasurement::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UDataPoint*>(TEXT("dataPoints"), DataPoints, Serializer);
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("units"), Units);		
}

void UDatabaseMeasurement ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UDataPoint*>(Bag->GetArrayField(TEXT("dataPoints")), DataPoints, OuterOwner);
	Name = Bag->GetStringField(TEXT("name"));
	Units = Bag->GetStringField(TEXT("units"));
}