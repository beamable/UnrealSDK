
#include "BeamableCore/Public/AutoGen/BeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponseLibrary::BeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponseToJsonString(const UBeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponse* Serializable, const bool Pretty)
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

UBeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponse* UBeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponseLibrary::Make(UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponse>(Outer);
	
	return Serializable;
}



