
#pragma once

#include "CoreMinimal.h"
#include "LeaderboardGetRanksRequestBody.h"

#include "LeaderboardGetRanksRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULeaderboardGetRanksRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LeaderboardGetRanksRequestBody To JSON String")
	static FString LeaderboardGetRanksRequestBodyToJsonString(const ULeaderboardGetRanksRequestBody* Serializable, const bool Pretty);		
};