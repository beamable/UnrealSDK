
#include "BeamableCore/Public/AutoGen/ServicePlanActorServicePlanLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UServicePlanActorServicePlanLibrary::ServicePlanActorServicePlanToJsonString(const UServicePlanActorServicePlan* Serializable, const bool Pretty)
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

UServicePlanActorServicePlan* UServicePlanActorServicePlanLibrary::Make(FString Name, UServicePlanActorDataDomain* DataDomain, FOptionalServicePlanActorServiceLimits ServiceLimits, FOptionalDateTime Created, UObject* Outer)
{
	auto Serializable = NewObject<UServicePlanActorServicePlan>(Outer);
	Serializable->Name = Name;
	Serializable->DataDomain = DataDomain;
	Serializable->ServiceLimits = ServiceLimits;
	Serializable->Created = Created;
	
	return Serializable;
}

void UServicePlanActorServicePlanLibrary::Break(const UServicePlanActorServicePlan* Serializable, FString& Name, UServicePlanActorDataDomain*& DataDomain, FOptionalServicePlanActorServiceLimits& ServiceLimits, FOptionalDateTime& Created)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		DataDomain = Serializable->DataDomain;
		ServiceLimits = Serializable->ServiceLimits;
		Created = Serializable->Created;
	}
		
}

