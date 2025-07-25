
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceStatusLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2ServiceStatusLibrary::BeamoV2ServiceStatusToJsonString(const UBeamoV2ServiceStatus* Serializable, const bool Pretty)
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

UBeamoV2ServiceStatus* UBeamoV2ServiceStatusLibrary::Make(FOptionalBool bIsCurrent, FOptionalBool bRunning, FOptionalString ServiceName, FOptionalString ImageId, FOptionalArrayOfBeamoV2ServiceDependencyReference ServiceDependencyReferences, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2ServiceStatus>(Outer);
	Serializable->bIsCurrent = bIsCurrent;
	Serializable->bRunning = bRunning;
	Serializable->ServiceName = ServiceName;
	Serializable->ImageId = ImageId;
	Serializable->ServiceDependencyReferences = ServiceDependencyReferences;
	
	return Serializable;
}

void UBeamoV2ServiceStatusLibrary::Break(const UBeamoV2ServiceStatus* Serializable, FOptionalBool& bIsCurrent, FOptionalBool& bRunning, FOptionalString& ServiceName, FOptionalString& ImageId, FOptionalArrayOfBeamoV2ServiceDependencyReference& ServiceDependencyReferences)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bIsCurrent = Serializable->bIsCurrent;
		bRunning = Serializable->bRunning;
		ServiceName = Serializable->ServiceName;
		ImageId = Serializable->ImageId;
		ServiceDependencyReferences = Serializable->ServiceDependencyReferences;
	}
		
}

