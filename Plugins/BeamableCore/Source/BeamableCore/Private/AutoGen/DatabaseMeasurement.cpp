
#include "BeamableCore/Public/AutoGen/DatabaseMeasurement.h"
#include "Serialization/BeamJsonUtils.h"




void UDatabaseMeasurement::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("units"), Units);
	UBeamJsonUtils::SerializeArray<UDataPoint*>(TEXT("dataPoints"), DataPoints, Serializer);
}

void UDatabaseMeasurement::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("units"), Units);
	UBeamJsonUtils::SerializeArray<UDataPoint*>(TEXT("dataPoints"), DataPoints, Serializer);		
}

void UDatabaseMeasurement::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("name")), Name);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("units")), Units);
	UBeamJsonUtils::DeserializeArray<UDataPoint*>(Bag->GetArrayField(TEXT("dataPoints")), DataPoints, OuterOwner);
}



