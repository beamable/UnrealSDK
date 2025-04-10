#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaderboardRemoveCacheEntryRequestBody.h"

#include "LeaderboardRemoveCacheEntryRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeaderboardRemoveCacheEntryRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|4 - Json", DisplayName="LeaderboardRemoveCacheEntryRequestBody To JSON String")
	static FString LeaderboardRemoveCacheEntryRequestBodyToJsonString(const ULeaderboardRemoveCacheEntryRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|3 - Backend", DisplayName="Make LeaderboardRemoveCacheEntryRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULeaderboardRemoveCacheEntryRequestBody* Make(int64 PlayerId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|3 - Backend", DisplayName="Break LeaderboardRemoveCacheEntryRequestBody", meta=(NativeBreakFunc))
	static void Break(const ULeaderboardRemoveCacheEntryRequestBody* Serializable, int64& PlayerId);
};