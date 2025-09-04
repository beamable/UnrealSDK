
#include "BeamableCore/Public/AutoGen/RealmsBasicBeamoLimitsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URealmsBasicBeamoLimitsLibrary::RealmsBasicBeamoLimitsToJsonString(const URealmsBasicBeamoLimits* Serializable, const bool Pretty)
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

URealmsBasicBeamoLimits* URealmsBasicBeamoLimitsLibrary::Make(FString MaxContainerSize, int32 MaxRunningContainersPerService, UObject* Outer)
{
	auto Serializable = NewObject<URealmsBasicBeamoLimits>(Outer);
	Serializable->MaxContainerSize = MaxContainerSize;
	Serializable->MaxRunningContainersPerService = MaxRunningContainersPerService;
	
	return Serializable;
}

void URealmsBasicBeamoLimitsLibrary::Break(const URealmsBasicBeamoLimits* Serializable, FString& MaxContainerSize, int32& MaxRunningContainersPerService)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		MaxContainerSize = Serializable->MaxContainerSize;
		MaxRunningContainersPerService = Serializable->MaxRunningContainersPerService;
	}
		
}

