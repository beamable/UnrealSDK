
#include "BeamableCore/Public/AutoGen/ServicePlanLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UServicePlanLibrary::ServicePlanToJsonString(const UServicePlan* Serializable, const bool Pretty)
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

UServicePlan* UServicePlanLibrary::Make(FString Name, UDataDomain* DataDomain, FOptionalString MinCustomerStatusSaved, FOptionalServiceLimits Limits, FOptionalInt64 Created, UObject* Outer)
{
	auto Serializable = NewObject<UServicePlan>(Outer);
	Serializable->Name = Name;
	Serializable->DataDomain = DataDomain;
	Serializable->MinCustomerStatusSaved = MinCustomerStatusSaved;
	Serializable->Limits = Limits;
	Serializable->Created = Created;
	
	return Serializable;
}

void UServicePlanLibrary::Break(const UServicePlan* Serializable, FString& Name, UDataDomain*& DataDomain, FOptionalString& MinCustomerStatusSaved, FOptionalServiceLimits& Limits, FOptionalInt64& Created)
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

