#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ChampionScore.h"

#include "ChampionScoreLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UChampionScoreLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|4 - Json", DisplayName="ChampionScore To JSON String")
	static FString ChampionScoreToJsonString(const UChampionScore* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|3 - Backend", DisplayName="Make ChampionScore", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UChampionScore* Make(int64 EndTimeMs, int64 StartTimeMs, double Score, int32 Cycle, int64 PlayerId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|3 - Backend", DisplayName="Break ChampionScore", meta=(NativeBreakFunc))
	static void Break(const UChampionScore* Serializable, int64& EndTimeMs, int64& StartTimeMs, double& Score, int32& Cycle, int64& PlayerId);
};