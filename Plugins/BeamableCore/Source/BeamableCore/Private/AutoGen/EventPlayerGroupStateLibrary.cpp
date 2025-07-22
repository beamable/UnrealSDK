
#include "BeamableCore/Public/AutoGen/EventPlayerGroupStateLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEventPlayerGroupStateLibrary::EventPlayerGroupStateToJsonString(const UEventPlayerGroupState* Serializable, const bool Pretty)
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

UEventPlayerGroupState* UEventPlayerGroupStateLibrary::Make(double GroupScore, int64 GroupRank, TArray<UEventRewardState*> RankRewards, TArray<UEventRewardState*> ScoreRewards, FOptionalString GroupId, UObject* Outer)
{
	auto Serializable = NewObject<UEventPlayerGroupState>(Outer);
	Serializable->GroupScore = GroupScore;
	Serializable->GroupRank = GroupRank;
	Serializable->RankRewards = RankRewards;
	Serializable->ScoreRewards = ScoreRewards;
	Serializable->GroupId = GroupId;
	
	return Serializable;
}

void UEventPlayerGroupStateLibrary::Break(const UEventPlayerGroupState* Serializable, double& GroupScore, int64& GroupRank, TArray<UEventRewardState*>& RankRewards, TArray<UEventRewardState*>& ScoreRewards, FOptionalString& GroupId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		GroupScore = Serializable->GroupScore;
		GroupRank = Serializable->GroupRank;
		RankRewards = Serializable->RankRewards;
		ScoreRewards = Serializable->ScoreRewards;
		GroupId = Serializable->GroupId;
	}
		
}

