
#include "BeamableCore/Public/AutoGen/StartServiceLogsRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UStartServiceLogsRequestBodyLibrary::StartServiceLogsRequestBodyToJsonString(const UStartServiceLogsRequestBody* Serializable, const bool Pretty)
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

UStartServiceLogsRequestBody* UStartServiceLogsRequestBodyLibrary::Make(FOptionalString ServiceName, FOptionalDateTime StartTime, FOptionalDateTime EndTime, FOptionalOrderDirection Order, FOptionalInt32 Limit, FOptionalArrayOfString Filters, UObject* Outer)
{
	auto Serializable = NewObject<UStartServiceLogsRequestBody>(Outer);
	Serializable->ServiceName = ServiceName;
	Serializable->StartTime = StartTime;
	Serializable->EndTime = EndTime;
	Serializable->Order = Order;
	Serializable->Limit = Limit;
	Serializable->Filters = Filters;
	
	return Serializable;
}

void UStartServiceLogsRequestBodyLibrary::Break(const UStartServiceLogsRequestBody* Serializable, FOptionalString& ServiceName, FOptionalDateTime& StartTime, FOptionalDateTime& EndTime, FOptionalOrderDirection& Order, FOptionalInt32& Limit, FOptionalArrayOfString& Filters)
{
	ServiceName = Serializable->ServiceName;
	StartTime = Serializable->StartTime;
	EndTime = Serializable->EndTime;
	Order = Serializable->Order;
	Limit = Serializable->Limit;
	Filters = Serializable->Filters;
		
}

