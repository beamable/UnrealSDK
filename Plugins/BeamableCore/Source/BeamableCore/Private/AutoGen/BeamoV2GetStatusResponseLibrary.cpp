
#include "BeamableCore/Public/AutoGen/BeamoV2GetStatusResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2GetStatusResponseLibrary::BeamoV2GetStatusResponseToJsonString(const UBeamoV2GetStatusResponse* Serializable, const bool Pretty)
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

UBeamoV2GetStatusResponse* UBeamoV2GetStatusResponseLibrary::Make(FOptionalBool bIsCurrent, FOptionalArrayOfBeamoV2ServiceStatus Services, FOptionalArrayOfBeamoV2ServiceStorageStatus StorageStatuses, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2GetStatusResponse>(Outer);
	Serializable->bIsCurrent = bIsCurrent;
	Serializable->Services = Services;
	Serializable->StorageStatuses = StorageStatuses;
	
	return Serializable;
}

void UBeamoV2GetStatusResponseLibrary::Break(const UBeamoV2GetStatusResponse* Serializable, FOptionalBool& bIsCurrent, FOptionalArrayOfBeamoV2ServiceStatus& Services, FOptionalArrayOfBeamoV2ServiceStorageStatus& StorageStatuses)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bIsCurrent = Serializable->bIsCurrent;
		Services = Serializable->Services;
		StorageStatuses = Serializable->StorageStatuses;
	}
		
}

