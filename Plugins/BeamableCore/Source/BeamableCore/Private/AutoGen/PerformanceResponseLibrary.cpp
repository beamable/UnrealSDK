
#include "BeamableCore/Public/AutoGen/PerformanceResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPerformanceResponseLibrary::PerformanceResponseToJsonString(const UPerformanceResponse* Serializable, const bool Pretty)
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

UPerformanceResponse* UPerformanceResponseLibrary::Make(UDatabaseMeasurements* DatabaseMeasurements, TArray<UPANamespace*> Namespaces, TArray<UPASuggestedIndex*> Indexes, TArray<UPASlowQuery*> Queries, UObject* Outer)
{
	auto Serializable = NewObject<UPerformanceResponse>(Outer);
	Serializable->DatabaseMeasurements = DatabaseMeasurements;
	Serializable->Namespaces = Namespaces;
	Serializable->Indexes = Indexes;
	Serializable->Queries = Queries;
	
	return Serializable;
}

void UPerformanceResponseLibrary::Break(const UPerformanceResponse* Serializable, UDatabaseMeasurements*& DatabaseMeasurements, TArray<UPANamespace*>& Namespaces, TArray<UPASuggestedIndex*>& Indexes, TArray<UPASlowQuery*>& Queries)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		DatabaseMeasurements = Serializable->DatabaseMeasurements;
		Namespaces = Serializable->Namespaces;
		Indexes = Serializable->Indexes;
		Queries = Serializable->Queries;
	}
		
}

