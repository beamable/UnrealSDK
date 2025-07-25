
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceStorageStatusLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2ServiceStorageStatusLibrary::BeamoV2ServiceStorageStatusToJsonString(const UBeamoV2ServiceStorageStatus* Serializable, const bool Pretty)
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

UBeamoV2ServiceStorageStatus* UBeamoV2ServiceStorageStatusLibrary::Make(FOptionalBool bIsCurrent, FOptionalBool bIsRunning, FOptionalString Id, FOptionalString StorageType, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2ServiceStorageStatus>(Outer);
	Serializable->bIsCurrent = bIsCurrent;
	Serializable->bIsRunning = bIsRunning;
	Serializable->Id = Id;
	Serializable->StorageType = StorageType;
	
	return Serializable;
}

void UBeamoV2ServiceStorageStatusLibrary::Break(const UBeamoV2ServiceStorageStatus* Serializable, FOptionalBool& bIsCurrent, FOptionalBool& bIsRunning, FOptionalString& Id, FOptionalString& StorageType)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bIsCurrent = Serializable->bIsCurrent;
		bIsRunning = Serializable->bIsRunning;
		Id = Serializable->Id;
		StorageType = Serializable->StorageType;
	}
		
}

