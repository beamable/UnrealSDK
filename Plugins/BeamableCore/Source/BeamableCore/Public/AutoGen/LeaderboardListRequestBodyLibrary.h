#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaderboardListRequestBody.h"

#include "LeaderboardListRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeaderboardListRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Json", DisplayName="LeaderboardListRequestBody To JSON String")
	static FString LeaderboardListRequestBodyToJsonString(const ULeaderboardListRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Make LeaderboardListRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bIncludePartitions, Skip, Limit, Prefix, Outer", NativeMakeFunc))
	static ULeaderboardListRequestBody* Make(FOptionalBool bIncludePartitions, FOptionalInt32 Skip, FOptionalInt32 Limit, FOptionalString Prefix, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Break LeaderboardListRequestBody", meta=(NativeBreakFunc))
	static void Break(const ULeaderboardListRequestBody* Serializable, FOptionalBool& bIncludePartitions, FOptionalInt32& Skip, FOptionalInt32& Limit, FOptionalString& Prefix);
};