#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MatchMakingWindowResp.h"

#include "MatchMakingWindowRespLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMatchMakingWindowRespLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|4 - Json", DisplayName="MatchMakingWindowResp To JSON String")
	static FString MatchMakingWindowRespToJsonString(const UMatchMakingWindowResp* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|3 - Backend", DisplayName="Make MatchMakingWindowResp", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMatchMakingWindowResp* Make(int32 Difficulty, TArray<UMatchMakingRanking*> Matches, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|3 - Backend", DisplayName="Break MatchMakingWindowResp", meta=(NativeBreakFunc))
	static void Break(const UMatchMakingWindowResp* Serializable, int32& Difficulty, TArray<UMatchMakingRanking*>& Matches);
};