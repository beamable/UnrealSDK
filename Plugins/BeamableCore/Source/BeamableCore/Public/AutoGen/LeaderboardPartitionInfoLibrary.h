#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaderboardPartitionInfo.h"

#include "LeaderboardPartitionInfoLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeaderboardPartitionInfoLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - LeaderboardPartitionInfo To JSON String")
	static FString LeaderboardPartitionInfoToJsonString(const ULeaderboardPartitionInfo* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make LeaderboardPartitionInfo", meta=(DefaultToSelf="Outer", AdvancedDisplay="Partition, Outer", NativeMakeFunc))
	static ULeaderboardPartitionInfo* Make(bool bIsEmpty, int64 PlayerId, FString LeaderboardId, FOptionalInt32 Partition, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break LeaderboardPartitionInfo", meta=(NativeBreakFunc))
	static void Break(const ULeaderboardPartitionInfo* Serializable, bool& bIsEmpty, int64& PlayerId, FString& LeaderboardId, FOptionalInt32& Partition);
};