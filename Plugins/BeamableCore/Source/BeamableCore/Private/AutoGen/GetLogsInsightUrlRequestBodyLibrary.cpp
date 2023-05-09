
#include "BeamableCore/Public/AutoGen/GetLogsInsightUrlRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UGetLogsInsightUrlRequestBodyLibrary::GetLogsInsightUrlRequestBodyToJsonString(const UGetLogsInsightUrlRequestBody* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UGetLogsInsightUrlRequestBody* UGetLogsInsightUrlRequestBodyLibrary::Make(FString ServiceName, FOptionalInt64 StartTime, FOptionalString Filter, FOptionalInt64 EndTime, FOptionalString Order, FOptionalInt32 Limit, UObject* Outer)
{
	auto Serializable = NewObject<UGetLogsInsightUrlRequestBody>(Outer);
	Serializable->ServiceName = ServiceName;
	Serializable->StartTime = StartTime;
	Serializable->Filter = Filter;
	Serializable->EndTime = EndTime;
	Serializable->Order = Order;
	Serializable->Limit = Limit;
	
	return Serializable;
}

void UGetLogsInsightUrlRequestBodyLibrary::Break(const UGetLogsInsightUrlRequestBody* Serializable, FString& ServiceName, FOptionalInt64& StartTime, FOptionalString& Filter, FOptionalInt64& EndTime, FOptionalString& Order, FOptionalInt32& Limit)
{
	ServiceName = Serializable->ServiceName;
	StartTime = Serializable->StartTime;
	Filter = Serializable->Filter;
	EndTime = Serializable->EndTime;
	Order = Serializable->Order;
	Limit = Serializable->Limit;
		
}

