
#include "BeamableCore/Public/AutoGen/StoragePerformanceLibrary.h"

#include "CoreMinimal.h"


FString UStoragePerformanceLibrary::StoragePerformanceToJsonString(const UStoragePerformance* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UStoragePerformance* UStoragePerformanceLibrary::Make(UDatabaseMeasurements* DatabaseMeasurements, TArray<UPANamespace*> Namespaces, TArray<UPASuggestedIndex*> Indexes, TArray<UPASlowQuery*> Queries, UObject* Outer)
{
	auto Serializable = NewObject<UStoragePerformance>(Outer);
	Serializable->DatabaseMeasurements = DatabaseMeasurements;
	Serializable->Namespaces = Namespaces;
	Serializable->Indexes = Indexes;
	Serializable->Queries = Queries;
	
	return Serializable;
}

void UStoragePerformanceLibrary::Break(const UStoragePerformance* Serializable, UDatabaseMeasurements*& DatabaseMeasurements, TArray<UPANamespace*>& Namespaces, TArray<UPASuggestedIndex*>& Indexes, TArray<UPASlowQuery*>& Queries)
{
	DatabaseMeasurements = Serializable->DatabaseMeasurements;
	Namespaces = Serializable->Namespaces;
	Indexes = Serializable->Indexes;
	Queries = Serializable->Queries;
		
}

