
#include "BeamableCore/Public/AutoGen/ServicePlanActorServiceLimitsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UServicePlanActorServiceLimitsLibrary::ServicePlanActorServiceLimitsToJsonString(const UServicePlanActorServiceLimits* Serializable, const bool Pretty)
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

UServicePlanActorServiceLimits* UServicePlanActorServiceLimitsLibrary::Make(FOptionalServicePlanActorBeamoLimits Beamo, UObject* Outer)
{
	auto Serializable = NewObject<UServicePlanActorServiceLimits>(Outer);
	Serializable->Beamo = Beamo;
	
	return Serializable;
}

void UServicePlanActorServiceLimitsLibrary::Break(const UServicePlanActorServiceLimits* Serializable, FOptionalServicePlanActorBeamoLimits& Beamo)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Beamo = Serializable->Beamo;
	}
		
}

