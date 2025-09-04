
#include "BeamableCore/Public/AutoGen/RealmsBasicServicePlanLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URealmsBasicServicePlanLibrary::RealmsBasicServicePlanToJsonString(const URealmsBasicServicePlan* Serializable, const bool Pretty)
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

URealmsBasicServicePlan* URealmsBasicServicePlanLibrary::Make(FString Name, URealmsBasicDataDomain* DataDomain, FOptionalString MinCustomerStatusSaved, FOptionalRealmsBasicServiceLimits Limits, FOptionalInt64 Created, UObject* Outer)
{
	auto Serializable = NewObject<URealmsBasicServicePlan>(Outer);
	Serializable->Name = Name;
	Serializable->DataDomain = DataDomain;
	Serializable->MinCustomerStatusSaved = MinCustomerStatusSaved;
	Serializable->Limits = Limits;
	Serializable->Created = Created;
	
	return Serializable;
}

void URealmsBasicServicePlanLibrary::Break(const URealmsBasicServicePlan* Serializable, FString& Name, URealmsBasicDataDomain*& DataDomain, FOptionalString& MinCustomerStatusSaved, FOptionalRealmsBasicServiceLimits& Limits, FOptionalInt64& Created)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		DataDomain = Serializable->DataDomain;
		MinCustomerStatusSaved = Serializable->MinCustomerStatusSaved;
		Limits = Serializable->Limits;
		Created = Serializable->Created;
	}
		
}

