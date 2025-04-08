#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaderboardPartitionRequestBody.h"

#include "LeaderboardPartitionRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeaderboardPartitionRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="LeaderboardPartitionRequestBody To JSON String")
	static FString LeaderboardPartitionRequestBodyToJsonString(const ULeaderboardPartitionRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make LeaderboardPartitionRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULeaderboardPartitionRequestBody* Make(int64 PlayerId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break LeaderboardPartitionRequestBody", meta=(NativeBreakFunc))
	static void Break(const ULeaderboardPartitionRequestBody* Serializable, int64& PlayerId);
};