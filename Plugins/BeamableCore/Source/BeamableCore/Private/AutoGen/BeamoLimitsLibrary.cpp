
#include "BeamableCore/Public/AutoGen/BeamoLimitsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoLimitsLibrary::BeamoLimitsToJsonString(const UBeamoLimits* Serializable, const bool Pretty)
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

UBeamoLimits* UBeamoLimitsLibrary::Make(FString MaxContainerSize, int32 MaxRunningContainersPerService, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoLimits>(Outer);
	Serializable->MaxContainerSize = MaxContainerSize;
	Serializable->MaxRunningContainersPerService = MaxRunningContainersPerService;
	
	return Serializable;
}

void UBeamoLimitsLibrary::Break(const UBeamoLimits* Serializable, FString& MaxContainerSize, int32& MaxRunningContainersPerService)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		MaxContainerSize = Serializable->MaxContainerSize;
		MaxRunningContainersPerService = Serializable->MaxRunningContainersPerService;
	}
		
}

