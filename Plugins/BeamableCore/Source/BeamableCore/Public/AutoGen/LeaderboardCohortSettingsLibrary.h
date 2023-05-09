#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaderboardCohortSettings.h"

#include "LeaderboardCohortSettingsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeaderboardCohortSettingsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - LeaderboardCohortSettings To JSON String")
	static FString LeaderboardCohortSettingsToJsonString(const ULeaderboardCohortSettings* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make LeaderboardCohortSettings", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULeaderboardCohortSettings* Make(TArray<ULeaderboardCohort*> Cohorts, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break LeaderboardCohortSettings", meta=(NativeBreakFunc))
	static void Break(const ULeaderboardCohortSettings* Serializable, TArray<ULeaderboardCohort*>& Cohorts);
};