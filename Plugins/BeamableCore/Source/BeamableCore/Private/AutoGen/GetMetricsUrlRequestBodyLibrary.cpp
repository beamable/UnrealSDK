
#include "BeamableCore/Public/AutoGen/GetMetricsUrlRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetMetricsUrlRequestBodyLibrary::GetMetricsUrlRequestBodyToJsonString(const UGetMetricsUrlRequestBody* Serializable, const bool Pretty)
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

UGetMetricsUrlRequestBody* UGetMetricsUrlRequestBodyLibrary::Make(FString ServiceName, FString MetricName, FOptionalInt64 StartTime, FOptionalInt64 EndTime, FOptionalInt32 Period, UObject* Outer)
{
	auto Serializable = NewObject<UGetMetricsUrlRequestBody>(Outer);
	Serializable->ServiceName = ServiceName;
	Serializable->MetricName = MetricName;
	Serializable->StartTime = StartTime;
	Serializable->EndTime = EndTime;
	Serializable->Period = Period;
	
	return Serializable;
}

void UGetMetricsUrlRequestBodyLibrary::Break(const UGetMetricsUrlRequestBody* Serializable, FString& ServiceName, FString& MetricName, FOptionalInt64& StartTime, FOptionalInt64& EndTime, FOptionalInt32& Period)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ServiceName = Serializable->ServiceName;
		MetricName = Serializable->MetricName;
		StartTime = Serializable->StartTime;
		EndTime = Serializable->EndTime;
		Period = Serializable->Period;
	}
		
}

