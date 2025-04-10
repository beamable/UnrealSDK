#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaderboardUidResponse.h"

#include "LeaderboardUidResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeaderboardUidResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|4 - Json", DisplayName="LeaderboardUidResponse To JSON String")
	static FString LeaderboardUidResponseToJsonString(const ULeaderboardUidResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|3 - Backend", DisplayName="Make LeaderboardUidResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULeaderboardUidResponse* Make(int64 Id, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|3 - Backend", DisplayName="Break LeaderboardUidResponse", meta=(NativeBreakFunc))
	static void Break(const ULeaderboardUidResponse* Serializable, int64& Id);
};