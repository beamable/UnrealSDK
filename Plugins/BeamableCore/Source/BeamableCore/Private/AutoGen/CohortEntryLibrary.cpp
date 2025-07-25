
#include "BeamableCore/Public/AutoGen/CohortEntryLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCohortEntryLibrary::CohortEntryToJsonString(const UCohortEntry* Serializable, const bool Pretty)
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

UCohortEntry* UCohortEntryLibrary::Make(FString Trial, FString Cohort, UObject* Outer)
{
	auto Serializable = NewObject<UCohortEntry>(Outer);
	Serializable->Trial = Trial;
	Serializable->Cohort = Cohort;
	
	return Serializable;
}

void UCohortEntryLibrary::Break(const UCohortEntry* Serializable, FString& Trial, FString& Cohort)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Trial = Serializable->Trial;
		Cohort = Serializable->Cohort;
	}
		
}

