
#include "BeamableCore/Public/AutoGen/EventLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEventLibrary::EventToJsonString(const UEvent* Serializable, const bool Pretty)
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

UEvent* UEventLibrary::Make(FString Name, FString StartDate, FString Symbol, TArray<UEventPhase*> Phases, FOptionalInt32 PartitionSize, FOptionalEventGroupRewards GroupRewards, FOptionalLeaderboardCohortSettings CohortSettings, FOptionalBeamClientPermission Permissions, FOptionalSchedule Schedule, FOptionalArrayOfString Stores, FOptionalArrayOfEventRewardContent ScoreRewards, FOptionalArrayOfEventRewardContent RankRewards, UObject* Outer)
{
	auto Serializable = NewObject<UEvent>(Outer);
	Serializable->Name = Name;
	Serializable->StartDate = StartDate;
	Serializable->Symbol = Symbol;
	Serializable->Phases = Phases;
	Serializable->PartitionSize = PartitionSize;
	Serializable->GroupRewards = GroupRewards;
	Serializable->CohortSettings = CohortSettings;
	Serializable->Permissions = Permissions;
	Serializable->Schedule = Schedule;
	Serializable->Stores = Stores;
	Serializable->ScoreRewards = ScoreRewards;
	Serializable->RankRewards = RankRewards;
	
	return Serializable;
}

void UEventLibrary::Break(const UEvent* Serializable, FString& Name, FString& StartDate, FString& Symbol, TArray<UEventPhase*>& Phases, FOptionalInt32& PartitionSize, FOptionalEventGroupRewards& GroupRewards, FOptionalLeaderboardCohortSettings& CohortSettings, FOptionalBeamClientPermission& Permissions, FOptionalSchedule& Schedule, FOptionalArrayOfString& Stores, FOptionalArrayOfEventRewardContent& ScoreRewards, FOptionalArrayOfEventRewardContent& RankRewards)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		StartDate = Serializable->StartDate;
		Symbol = Serializable->Symbol;
		Phases = Serializable->Phases;
		PartitionSize = Serializable->PartitionSize;
		GroupRewards = Serializable->GroupRewards;
		CohortSettings = Serializable->CohortSettings;
		Permissions = Serializable->Permissions;
		Schedule = Serializable->Schedule;
		Stores = Serializable->Stores;
		ScoreRewards = Serializable->ScoreRewards;
		RankRewards = Serializable->RankRewards;
	}
		
}

