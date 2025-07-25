
#include "BeamableCore/Public/AutoGen/EntitlementRequirementLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEntitlementRequirementLibrary::EntitlementRequirementToJsonString(const UEntitlementRequirement* Serializable, const bool Pretty)
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

UEntitlementRequirement* UEntitlementRequirementLibrary::Make(FString Symbol, FString Constraint, FString State, FOptionalString Specialization, UObject* Outer)
{
	auto Serializable = NewObject<UEntitlementRequirement>(Outer);
	Serializable->Symbol = Symbol;
	Serializable->Constraint = Constraint;
	Serializable->State = State;
	Serializable->Specialization = Specialization;
	
	return Serializable;
}

void UEntitlementRequirementLibrary::Break(const UEntitlementRequirement* Serializable, FString& Symbol, FString& Constraint, FString& State, FOptionalString& Specialization)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Symbol = Serializable->Symbol;
		Constraint = Serializable->Constraint;
		State = Serializable->State;
		Specialization = Serializable->Specialization;
	}
		
}

