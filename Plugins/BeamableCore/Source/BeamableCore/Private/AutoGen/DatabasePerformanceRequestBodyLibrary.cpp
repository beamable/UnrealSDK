
#include "BeamableCore/Public/AutoGen/DatabasePerformanceRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UDatabasePerformanceRequestBodyLibrary::DatabasePerformanceRequestBodyToJsonString(const UDatabasePerformanceRequestBody* Serializable, const bool Pretty)
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

UDatabasePerformanceRequestBody* UDatabasePerformanceRequestBodyLibrary::Make(FString StorageObjectName, FString Granularity, FOptionalString EndDate, FOptionalString StartDate, FOptionalString Period, UObject* Outer)
{
	auto Serializable = NewObject<UDatabasePerformanceRequestBody>(Outer);
	Serializable->StorageObjectName = StorageObjectName;
	Serializable->Granularity = Granularity;
	Serializable->EndDate = EndDate;
	Serializable->StartDate = StartDate;
	Serializable->Period = Period;
	
	return Serializable;
}

void UDatabasePerformanceRequestBodyLibrary::Break(const UDatabasePerformanceRequestBody* Serializable, FString& StorageObjectName, FString& Granularity, FOptionalString& EndDate, FOptionalString& StartDate, FOptionalString& Period)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		StorageObjectName = Serializable->StorageObjectName;
		Granularity = Serializable->Granularity;
		EndDate = Serializable->EndDate;
		StartDate = Serializable->StartDate;
		Period = Serializable->Period;
	}
		
}

