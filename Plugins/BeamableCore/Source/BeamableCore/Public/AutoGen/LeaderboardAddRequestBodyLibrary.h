#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaderboardAddRequestBody.h"

#include "LeaderboardAddRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeaderboardAddRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Json", DisplayName="LeaderboardAddRequestBody To JSON String")
	static FString LeaderboardAddRequestBodyToJsonString(const ULeaderboardAddRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Make LeaderboardAddRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bIncrement, MaxScore, MinScore, Stats, Outer", NativeMakeFunc))
	static ULeaderboardAddRequestBody* Make(double Score, int64 Id, FOptionalBool bIncrement, FOptionalDouble MaxScore, FOptionalDouble MinScore, FOptionalMapOfString Stats, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Break LeaderboardAddRequestBody", meta=(NativeBreakFunc))
	static void Break(const ULeaderboardAddRequestBody* Serializable, double& Score, int64& Id, FOptionalBool& bIncrement, FOptionalDouble& MaxScore, FOptionalDouble& MinScore, FOptionalMapOfString& Stats);
};