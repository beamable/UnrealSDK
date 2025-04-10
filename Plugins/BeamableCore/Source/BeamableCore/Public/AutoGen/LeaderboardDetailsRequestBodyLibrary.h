#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaderboardDetailsRequestBody.h"

#include "LeaderboardDetailsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeaderboardDetailsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Json", DisplayName="LeaderboardDetailsRequestBody To JSON String")
	static FString LeaderboardDetailsRequestBodyToJsonString(const ULeaderboardDetailsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Make LeaderboardDetailsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="From, Max, Outer", NativeMakeFunc))
	static ULeaderboardDetailsRequestBody* Make(FOptionalInt32 From, FOptionalInt32 Max, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Break LeaderboardDetailsRequestBody", meta=(NativeBreakFunc))
	static void Break(const ULeaderboardDetailsRequestBody* Serializable, FOptionalInt32& From, FOptionalInt32& Max);
};