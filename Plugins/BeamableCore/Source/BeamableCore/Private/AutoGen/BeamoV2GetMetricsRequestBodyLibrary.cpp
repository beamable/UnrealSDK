
#include "BeamableCore/Public/AutoGen/BeamoV2GetMetricsRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2GetMetricsRequestBodyLibrary::BeamoV2GetMetricsRequestBodyToJsonString(const UBeamoV2GetMetricsRequestBody* Serializable, const bool Pretty)
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

UBeamoV2GetMetricsRequestBody* UBeamoV2GetMetricsRequestBodyLibrary::Make(FOptionalString MetricName, FOptionalDateTime StartTime, FOptionalDateTime EndTime, FOptionalInt32 Period, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2GetMetricsRequestBody>(Outer);
	Serializable->MetricName = MetricName;
	Serializable->StartTime = StartTime;
	Serializable->EndTime = EndTime;
	Serializable->Period = Period;
	
	return Serializable;
}

void UBeamoV2GetMetricsRequestBodyLibrary::Break(const UBeamoV2GetMetricsRequestBody* Serializable, FOptionalString& MetricName, FOptionalDateTime& StartTime, FOptionalDateTime& EndTime, FOptionalInt32& Period)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		MetricName = Serializable->MetricName;
		StartTime = Serializable->StartTime;
		EndTime = Serializable->EndTime;
		Period = Serializable->Period;
	}
		
}

