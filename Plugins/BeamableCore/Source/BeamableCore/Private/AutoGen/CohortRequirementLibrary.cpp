
#include "BeamableCore/Public/AutoGen/CohortRequirementLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCohortRequirementLibrary::CohortRequirementToJsonString(const UCohortRequirement* Serializable, const bool Pretty)
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

UCohortRequirement* UCohortRequirementLibrary::Make(FString Trial, FString Cohort, FString Constraint, UObject* Outer)
{
	auto Serializable = NewObject<UCohortRequirement>(Outer);
	Serializable->Trial = Trial;
	Serializable->Cohort = Cohort;
	Serializable->Constraint = Constraint;
	
	return Serializable;
}

void UCohortRequirementLibrary::Break(const UCohortRequirement* Serializable, FString& Trial, FString& Cohort, FString& Constraint)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Trial = Serializable->Trial;
		Cohort = Serializable->Cohort;
		Constraint = Serializable->Constraint;
	}
		
}

