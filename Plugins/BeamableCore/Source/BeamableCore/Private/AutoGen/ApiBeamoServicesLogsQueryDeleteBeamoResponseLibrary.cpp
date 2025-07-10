
#include "BeamableCore/Public/AutoGen/ApiBeamoServicesLogsQueryDeleteBeamoResponseLibrary.h"

#include "CoreMinimal.h"


FString UApiBeamoServicesLogsQueryDeleteBeamoResponseLibrary::ApiBeamoServicesLogsQueryDeleteBeamoResponseToJsonString(const UApiBeamoServicesLogsQueryDeleteBeamoResponse* Serializable, const bool Pretty)
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

UApiBeamoServicesLogsQueryDeleteBeamoResponse* UApiBeamoServicesLogsQueryDeleteBeamoResponseLibrary::Make(UObject* Outer)
{
	auto Serializable = NewObject<UApiBeamoServicesLogsQueryDeleteBeamoResponse>(Outer);
	
	return Serializable;
}



