
#include "BeamableCore/Public/AutoGen/ServicePlanActorBeamoLimitsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UServicePlanActorBeamoLimitsLibrary::ServicePlanActorBeamoLimitsToJsonString(const UServicePlanActorBeamoLimits* Serializable, const bool Pretty)
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

UServicePlanActorBeamoLimits* UServicePlanActorBeamoLimitsLibrary::Make(UObject* Outer)
{
	auto Serializable = NewObject<UServicePlanActorBeamoLimits>(Outer);
	
	return Serializable;
}



