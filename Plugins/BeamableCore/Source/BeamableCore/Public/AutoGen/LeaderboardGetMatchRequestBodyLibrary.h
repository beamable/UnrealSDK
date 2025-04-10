#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaderboardGetMatchRequestBody.h"

#include "LeaderboardGetMatchRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeaderboardGetMatchRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Json", DisplayName="LeaderboardGetMatchRequestBody To JSON String")
	static FString LeaderboardGetMatchRequestBodyToJsonString(const ULeaderboardGetMatchRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Make LeaderboardGetMatchRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULeaderboardGetMatchRequestBody* Make(int32 PoolSize, int32 Windows, int32 WindowSize, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Break LeaderboardGetMatchRequestBody", meta=(NativeBreakFunc))
	static void Break(const ULeaderboardGetMatchRequestBody* Serializable, int32& PoolSize, int32& Windows, int32& WindowSize);
};