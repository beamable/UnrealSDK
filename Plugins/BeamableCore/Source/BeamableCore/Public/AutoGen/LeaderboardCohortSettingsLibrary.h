
#pragma once

#include "CoreMinimal.h"
#include "LeaderboardCohortSettings.h"

#include "LeaderboardCohortSettingsLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULeaderboardCohortSettingsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LeaderboardCohortSettings To JSON String")
	static FString LeaderboardCohortSettingsToJsonString(const ULeaderboardCohortSettings* Serializable, const bool Pretty);		
};