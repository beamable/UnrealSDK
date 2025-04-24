#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaderboardApiViewRequestBody.h"

#include "LeaderboardApiViewRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeaderboardApiViewRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Json", DisplayName="LeaderboardApiViewRequestBody To JSON String")
	static FString LeaderboardApiViewRequestBodyToJsonString(const ULeaderboardApiViewRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Make LeaderboardApiViewRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bFriends, bGuild, Max, Focus, From, Outlier, Outer", NativeMakeFunc))
	static ULeaderboardApiViewRequestBody* Make(FOptionalBool bFriends, FOptionalBool bGuild, FOptionalInt32 Max, FOptionalInt64 Focus, FOptionalInt32 From, FOptionalInt64 Outlier, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Break LeaderboardApiViewRequestBody", meta=(NativeBreakFunc))
	static void Break(const ULeaderboardApiViewRequestBody* Serializable, FOptionalBool& bFriends, FOptionalBool& bGuild, FOptionalInt32& Max, FOptionalInt64& Focus, FOptionalInt32& From, FOptionalInt64& Outlier);
};