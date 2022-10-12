
#pragma once

#include "CoreMinimal.h"
#include "LeaderboardUidResponse.h"

#include "LeaderboardUidResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULeaderboardUidResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LeaderboardUidResponse To JSON String")
	static FString LeaderboardUidResponseToJsonString(const ULeaderboardUidResponse* Serializable, const bool Pretty);		
};