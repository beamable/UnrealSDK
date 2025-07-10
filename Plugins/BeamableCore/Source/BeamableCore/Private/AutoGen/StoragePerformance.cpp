
#include "BeamableCore/Public/AutoGen/StoragePerformance.h"
#include "Serialization/BeamJsonUtils.h"



void UStoragePerformance::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UStoragePerformance::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UDatabaseMeasurements*>("databaseMeasurements", DatabaseMeasurements, Serializer);
	UBeamJsonUtils::SerializeArray<UPANamespace*>(TEXT("namespaces"), Namespaces, Serializer);
	UBeamJsonUtils::SerializeArray<UPASuggestedIndex*>(TEXT("indexes"), Indexes, Serializer);
	UBeamJsonUtils::SerializeArray<UPASlowQuery*>(TEXT("queries"), Queries, Serializer);
}

void UStoragePerformance::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UDatabaseMeasurements*>("databaseMeasurements", DatabaseMeasurements, Serializer);
	UBeamJsonUtils::SerializeArray<UPANamespace*>(TEXT("namespaces"), Namespaces, Serializer);
	UBeamJsonUtils::SerializeArray<UPASuggestedIndex*>(TEXT("indexes"), Indexes, Serializer);
	UBeamJsonUtils::SerializeArray<UPASlowQuery*>(TEXT("queries"), Queries, Serializer);		
}

void UStoragePerformance::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<UDatabaseMeasurements*>("databaseMeasurements", Bag, DatabaseMeasurements, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UPANamespace*>(Bag->GetArrayField(TEXT("namespaces")), Namespaces, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UPASuggestedIndex*>(Bag->GetArrayField(TEXT("indexes")), Indexes, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UPASlowQuery*>(Bag->GetArrayField(TEXT("queries")), Queries, OuterOwner);
}



