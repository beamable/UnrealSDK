
#include "BeamableCore/Public/AutoGen/BeamoV2StartServiceLogsRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2StartServiceLogsRequestBodyLibrary::BeamoV2StartServiceLogsRequestBodyToJsonString(const UBeamoV2StartServiceLogsRequestBody* Serializable, const bool Pretty)
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

UBeamoV2StartServiceLogsRequestBody* UBeamoV2StartServiceLogsRequestBodyLibrary::Make(FOptionalString ServiceName, FOptionalDateTime StartTime, FOptionalDateTime EndTime, FOptionalBeamoV2OrderDirection Order, FOptionalInt32 Limit, FOptionalArrayOfString Filters, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2StartServiceLogsRequestBody>(Outer);
	Serializable->ServiceName = ServiceName;
	Serializable->StartTime = StartTime;
	Serializable->EndTime = EndTime;
	Serializable->Order = Order;
	Serializable->Limit = Limit;
	Serializable->Filters = Filters;
	
	return Serializable;
}

void UBeamoV2StartServiceLogsRequestBodyLibrary::Break(const UBeamoV2StartServiceLogsRequestBody* Serializable, FOptionalString& ServiceName, FOptionalDateTime& StartTime, FOptionalDateTime& EndTime, FOptionalBeamoV2OrderDirection& Order, FOptionalInt32& Limit, FOptionalArrayOfString& Filters)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ServiceName = Serializable->ServiceName;
		StartTime = Serializable->StartTime;
		EndTime = Serializable->EndTime;
		Order = Serializable->Order;
		Limit = Serializable->Limit;
		Filters = Serializable->Filters;
	}
		
}

