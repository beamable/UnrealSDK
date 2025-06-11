#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventPlayerStateView.h"

#include "EventPlayerStateViewLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventPlayerStateViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Json", DisplayName="EventPlayerStateView To JSON String")
	static FString EventPlayerStateViewToJsonString(const UEventPlayerStateView* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Make/Break", DisplayName="Make EventPlayerStateView", meta=(DefaultToSelf="Outer", AdvancedDisplay="CurrentPhase, GroupRewards, Outer", NativeMakeFunc))
	static UEventPlayerStateView* Make(bool bRunning, FString Name, int64 Rank, double Score, int64 SecondsRemaining, FString Id, FString LeaderboardId, TArray<UEventPlayerPhaseView*> AllPhases, TArray<UEventRewardState*> RankRewards, TArray<UEventRewardState*> ScoreRewards, FOptionalEventPlayerPhaseView CurrentPhase, FOptionalEventPlayerGroupState GroupRewards, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Make/Break", DisplayName="Break EventPlayerStateView", meta=(NativeBreakFunc))
	static void Break(const UEventPlayerStateView* Serializable, bool& bRunning, FString& Name, int64& Rank, double& Score, int64& SecondsRemaining, FString& Id, FString& LeaderboardId, TArray<UEventPlayerPhaseView*>& AllPhases, TArray<UEventRewardState*>& RankRewards, TArray<UEventRewardState*>& ScoreRewards, FOptionalEventPlayerPhaseView& CurrentPhase, FOptionalEventPlayerGroupState& GroupRewards);
};