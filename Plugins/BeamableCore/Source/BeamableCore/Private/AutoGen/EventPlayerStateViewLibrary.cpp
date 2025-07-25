
#include "BeamableCore/Public/AutoGen/EventPlayerStateViewLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEventPlayerStateViewLibrary::EventPlayerStateViewToJsonString(const UEventPlayerStateView* Serializable, const bool Pretty)
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

UEventPlayerStateView* UEventPlayerStateViewLibrary::Make(bool bRunning, FString Name, int64 Rank, double Score, int64 SecondsRemaining, FString Id, FString LeaderboardId, TArray<UEventPlayerPhaseView*> AllPhases, TArray<UEventRewardState*> RankRewards, TArray<UEventRewardState*> ScoreRewards, FOptionalEventPlayerPhaseView CurrentPhase, FOptionalEventPlayerGroupState GroupRewards, UObject* Outer)
{
	auto Serializable = NewObject<UEventPlayerStateView>(Outer);
	Serializable->bRunning = bRunning;
	Serializable->Name = Name;
	Serializable->Rank = Rank;
	Serializable->Score = Score;
	Serializable->SecondsRemaining = SecondsRemaining;
	Serializable->Id = Id;
	Serializable->LeaderboardId = LeaderboardId;
	Serializable->AllPhases = AllPhases;
	Serializable->RankRewards = RankRewards;
	Serializable->ScoreRewards = ScoreRewards;
	Serializable->CurrentPhase = CurrentPhase;
	Serializable->GroupRewards = GroupRewards;
	
	return Serializable;
}

void UEventPlayerStateViewLibrary::Break(const UEventPlayerStateView* Serializable, bool& bRunning, FString& Name, int64& Rank, double& Score, int64& SecondsRemaining, FString& Id, FString& LeaderboardId, TArray<UEventPlayerPhaseView*>& AllPhases, TArray<UEventRewardState*>& RankRewards, TArray<UEventRewardState*>& ScoreRewards, FOptionalEventPlayerPhaseView& CurrentPhase, FOptionalEventPlayerGroupState& GroupRewards)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bRunning = Serializable->bRunning;
		Name = Serializable->Name;
		Rank = Serializable->Rank;
		Score = Serializable->Score;
		SecondsRemaining = Serializable->SecondsRemaining;
		Id = Serializable->Id;
		LeaderboardId = Serializable->LeaderboardId;
		AllPhases = Serializable->AllPhases;
		RankRewards = Serializable->RankRewards;
		ScoreRewards = Serializable->ScoreRewards;
		CurrentPhase = Serializable->CurrentPhase;
		GroupRewards = Serializable->GroupRewards;
	}
		
}

