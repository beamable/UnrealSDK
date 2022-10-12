
#pragma once

#include "CoreMinimal.h"
#include "LeaderboardRemoveCacheEntryRequestBody.h"

#include "LeaderboardRemoveCacheEntryRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULeaderboardRemoveCacheEntryRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LeaderboardRemoveCacheEntryRequestBody To JSON String")
	static FString LeaderboardRemoveCacheEntryRequestBodyToJsonString(const ULeaderboardRemoveCacheEntryRequestBody* Serializable, const bool Pretty);		
};