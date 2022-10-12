
#pragma once

#include "CoreMinimal.h"
#include "LeaderboardPartitionInfo.h"

#include "LeaderboardPartitionInfoLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULeaderboardPartitionInfoLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LeaderboardPartitionInfo To JSON String")
	static FString LeaderboardPartitionInfoToJsonString(const ULeaderboardPartitionInfo* Serializable, const bool Pretty);		
};