#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaderboardGetRanksRequestBody.h"

#include "LeaderboardGetRanksRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeaderboardGetRanksRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - LeaderboardGetRanksRequestBody To JSON String")
	static FString LeaderboardGetRanksRequestBodyToJsonString(const ULeaderboardGetRanksRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make LeaderboardGetRanksRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULeaderboardGetRanksRequestBody* Make(FString Ids, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break LeaderboardGetRanksRequestBody", meta=(NativeBreakFunc))
	static void Break(const ULeaderboardGetRanksRequestBody* Serializable, FString& Ids);
};