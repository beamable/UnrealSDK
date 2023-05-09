#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaderboardListRequestBody.h"

#include "LeaderboardListRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeaderboardListRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - LeaderboardListRequestBody To JSON String")
	static FString LeaderboardListRequestBodyToJsonString(const ULeaderboardListRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make LeaderboardListRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Skip, Limit, Outer", NativeMakeFunc))
	static ULeaderboardListRequestBody* Make(FOptionalInt32 Skip, FOptionalInt32 Limit, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break LeaderboardListRequestBody", meta=(NativeBreakFunc))
	static void Break(const ULeaderboardListRequestBody* Serializable, FOptionalInt32& Skip, FOptionalInt32& Limit);
};