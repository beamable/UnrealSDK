
#pragma once

#include "CoreMinimal.h"
#include "LeaderboardCohort.h"

#include "LeaderboardCohortLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULeaderboardCohortLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LeaderboardCohort To JSON String")
	static FString LeaderboardCohortToJsonString(const ULeaderboardCohort* Serializable, const bool Pretty);		
};