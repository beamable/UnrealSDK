
#include "BeamableCore/Public/AutoGen/GetMetricsRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UGetMetricsRequestBodyLibrary::GetMetricsRequestBodyToJsonString(const UGetMetricsRequestBody* Serializable, const bool Pretty)
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

UGetMetricsRequestBody* UGetMetricsRequestBodyLibrary::Make(FOptionalString MetricName, FOptionalDateTime StartTime, FOptionalDateTime EndTime, FOptionalInt32 Period, UObject* Outer)
{
	auto Serializable = NewObject<UGetMetricsRequestBody>(Outer);
	Serializable->MetricName = MetricName;
	Serializable->StartTime = StartTime;
	Serializable->EndTime = EndTime;
	Serializable->Period = Period;
	
	return Serializable;
}

void UGetMetricsRequestBodyLibrary::Break(const UGetMetricsRequestBody* Serializable, FOptionalString& MetricName, FOptionalDateTime& StartTime, FOptionalDateTime& EndTime, FOptionalInt32& Period)
{
	MetricName = Serializable->MetricName;
	StartTime = Serializable->StartTime;
	EndTime = Serializable->EndTime;
	Period = Serializable->Period;
		
}

