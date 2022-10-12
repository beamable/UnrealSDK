
#include "AutoGen/PerformanceResponse.h"
#include "Serialization/BeamJsonUtils.h"


void UPerformanceResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UPANamespace*>(TEXT("namespaces"), Namespaces, Serializer);
	UBeamJsonUtils::SerializeArray<UPASuggestedIndex*>(TEXT("indexes"), Indexes, Serializer);
	UBeamJsonUtils::SerializeArray<UPASlowQuery*>(TEXT("queries"), Queries, Serializer);
	UBeamJsonUtils::SerializeUObject<UDatabaseMeasurements*>("databaseMeasurements", DatabaseMeasurements, Serializer);
}

void UPerformanceResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UPANamespace*>(TEXT("namespaces"), Namespaces, Serializer);
	UBeamJsonUtils::SerializeArray<UPASuggestedIndex*>(TEXT("indexes"), Indexes, Serializer);
	UBeamJsonUtils::SerializeArray<UPASlowQuery*>(TEXT("queries"), Queries, Serializer);
	UBeamJsonUtils::SerializeUObject<UDatabaseMeasurements*>("databaseMeasurements", DatabaseMeasurements, Serializer);		
}

void UPerformanceResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UPANamespace*>(Bag->GetArrayField(TEXT("namespaces")), Namespaces, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UPASuggestedIndex*>(Bag->GetArrayField(TEXT("indexes")), Indexes, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UPASlowQuery*>(Bag->GetArrayField(TEXT("queries")), Queries, OuterOwner);
	UBeamJsonUtils::DeserializeUObject<UDatabaseMeasurements*>("databaseMeasurements", Bag, DatabaseMeasurements, OuterOwner);
}