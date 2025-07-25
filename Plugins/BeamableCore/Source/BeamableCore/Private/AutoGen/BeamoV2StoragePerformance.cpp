
#include "BeamableCore/Public/AutoGen/BeamoV2StoragePerformance.h"
#include "Serialization/BeamJsonUtils.h"



void UBeamoV2StoragePerformance::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UBeamoV2StoragePerformance::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UBeamoV2DatabaseMeasurements*>("databaseMeasurements", DatabaseMeasurements, Serializer);
	UBeamJsonUtils::SerializeArray<UBeamoV2PANamespace*>(TEXT("namespaces"), Namespaces, Serializer);
	UBeamJsonUtils::SerializeArray<UBeamoV2PASuggestedIndex*>(TEXT("indexes"), Indexes, Serializer);
	UBeamJsonUtils::SerializeArray<UBeamoV2PASlowQuery*>(TEXT("queries"), Queries, Serializer);
}

void UBeamoV2StoragePerformance::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UBeamoV2DatabaseMeasurements*>("databaseMeasurements", DatabaseMeasurements, Serializer);
	UBeamJsonUtils::SerializeArray<UBeamoV2PANamespace*>(TEXT("namespaces"), Namespaces, Serializer);
	UBeamJsonUtils::SerializeArray<UBeamoV2PASuggestedIndex*>(TEXT("indexes"), Indexes, Serializer);
	UBeamJsonUtils::SerializeArray<UBeamoV2PASlowQuery*>(TEXT("queries"), Queries, Serializer);		
}

void UBeamoV2StoragePerformance::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<UBeamoV2DatabaseMeasurements*>("databaseMeasurements", Bag, DatabaseMeasurements, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UBeamoV2PANamespace*>(Bag->GetArrayField(TEXT("namespaces")), Namespaces, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UBeamoV2PASuggestedIndex*>(Bag->GetArrayField(TEXT("indexes")), Indexes, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UBeamoV2PASlowQuery*>(Bag->GetArrayField(TEXT("queries")), Queries, OuterOwner);
}



