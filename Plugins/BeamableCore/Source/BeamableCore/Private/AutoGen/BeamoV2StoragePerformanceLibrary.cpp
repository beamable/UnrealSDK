
#include "BeamableCore/Public/AutoGen/BeamoV2StoragePerformanceLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2StoragePerformanceLibrary::BeamoV2StoragePerformanceToJsonString(const UBeamoV2StoragePerformance* Serializable, const bool Pretty)
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

UBeamoV2StoragePerformance* UBeamoV2StoragePerformanceLibrary::Make(UBeamoV2DatabaseMeasurements* DatabaseMeasurements, TArray<UBeamoV2PANamespace*> Namespaces, TArray<UBeamoV2PASuggestedIndex*> Indexes, TArray<UBeamoV2PASlowQuery*> Queries, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2StoragePerformance>(Outer);
	Serializable->DatabaseMeasurements = DatabaseMeasurements;
	Serializable->Namespaces = Namespaces;
	Serializable->Indexes = Indexes;
	Serializable->Queries = Queries;
	
	return Serializable;
}

void UBeamoV2StoragePerformanceLibrary::Break(const UBeamoV2StoragePerformance* Serializable, UBeamoV2DatabaseMeasurements*& DatabaseMeasurements, TArray<UBeamoV2PANamespace*>& Namespaces, TArray<UBeamoV2PASuggestedIndex*>& Indexes, TArray<UBeamoV2PASlowQuery*>& Queries)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		DatabaseMeasurements = Serializable->DatabaseMeasurements;
		Namespaces = Serializable->Namespaces;
		Indexes = Serializable->Indexes;
		Queries = Serializable->Queries;
	}
		
}

