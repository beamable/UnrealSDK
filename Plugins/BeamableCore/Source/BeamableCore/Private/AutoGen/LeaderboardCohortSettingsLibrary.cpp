
#include "BeamableCore/Public/AutoGen/LeaderboardCohortSettingsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULeaderboardCohortSettingsLibrary::LeaderboardCohortSettingsToJsonString(const ULeaderboardCohortSettings* Serializable, const bool Pretty)
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

ULeaderboardCohortSettings* ULeaderboardCohortSettingsLibrary::Make(TArray<ULeaderboardCohort*> Cohorts, UObject* Outer)
{
	auto Serializable = NewObject<ULeaderboardCohortSettings>(Outer);
	Serializable->Cohorts = Cohorts;
	
	return Serializable;
}

void ULeaderboardCohortSettingsLibrary::Break(const ULeaderboardCohortSettings* Serializable, TArray<ULeaderboardCohort*>& Cohorts)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Cohorts = Serializable->Cohorts;
	}
		
}

