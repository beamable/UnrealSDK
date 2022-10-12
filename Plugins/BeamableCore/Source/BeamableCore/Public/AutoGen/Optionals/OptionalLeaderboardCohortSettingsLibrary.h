

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalLeaderboardCohortSettings.h"

#include "OptionalLeaderboardCohortSettingsLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalLeaderboardCohortSettingsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalLeaderboardCohortSettings MakeOptionalLeaderboardCohortSettings(ULeaderboardCohortSettings* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "LeaderboardCohortSettings To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalLeaderboardCohortSettings Conv_OptionalLeaderboardCohortSettingsFromValue(ULeaderboardCohortSettings* Value);
};
