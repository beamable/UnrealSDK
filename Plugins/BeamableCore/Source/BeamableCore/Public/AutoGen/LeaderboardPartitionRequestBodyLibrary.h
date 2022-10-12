
#pragma once

#include "CoreMinimal.h"
#include "LeaderboardPartitionRequestBody.h"

#include "LeaderboardPartitionRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULeaderboardPartitionRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LeaderboardPartitionRequestBody To JSON String")
	static FString LeaderboardPartitionRequestBodyToJsonString(const ULeaderboardPartitionRequestBody* Serializable, const bool Pretty);		
};