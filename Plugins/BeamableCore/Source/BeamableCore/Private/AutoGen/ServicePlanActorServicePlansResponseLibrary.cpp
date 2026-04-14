
#include "BeamableCore/Public/AutoGen/ServicePlanActorServicePlansResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UServicePlanActorServicePlansResponseLibrary::ServicePlanActorServicePlansResponseToJsonString(const UServicePlanActorServicePlansResponse* Serializable, const bool Pretty)
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

UServicePlanActorServicePlansResponse* UServicePlanActorServicePlansResponseLibrary::Make(FOptionalArrayOfServicePlanActorServicePlan Plans, UObject* Outer)
{
	auto Serializable = NewObject<UServicePlanActorServicePlansResponse>(Outer);
	Serializable->Plans = Plans;
	
	return Serializable;
}

void UServicePlanActorServicePlansResponseLibrary::Break(const UServicePlanActorServicePlansResponse* Serializable, FOptionalArrayOfServicePlanActorServicePlan& Plans)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Plans = Serializable->Plans;
	}
		
}

