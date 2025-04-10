#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventPlayerGroupState.h"

#include "EventPlayerGroupStateLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventPlayerGroupStateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Json", DisplayName="EventPlayerGroupState To JSON String")
	static FString EventPlayerGroupStateToJsonString(const UEventPlayerGroupState* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Make/Break", DisplayName="Make EventPlayerGroupState", meta=(DefaultToSelf="Outer", AdvancedDisplay="GroupId, Outer", NativeMakeFunc))
	static UEventPlayerGroupState* Make(double GroupScore, int64 GroupRank, TArray<UEventRewardState*> RankRewards, TArray<UEventRewardState*> ScoreRewards, FOptionalString GroupId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Make/Break", DisplayName="Break EventPlayerGroupState", meta=(NativeBreakFunc))
	static void Break(const UEventPlayerGroupState* Serializable, double& GroupScore, int64& GroupRank, TArray<UEventRewardState*>& RankRewards, TArray<UEventRewardState*>& ScoreRewards, FOptionalString& GroupId);
};