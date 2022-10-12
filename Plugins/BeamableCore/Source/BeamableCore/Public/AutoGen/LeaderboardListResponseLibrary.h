
#pragma once

#include "CoreMinimal.h"
#include "LeaderboardListResponse.h"

#include "LeaderboardListResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULeaderboardListResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LeaderboardListResponse To JSON String")
	static FString LeaderboardListResponseToJsonString(const ULeaderboardListResponse* Serializable, const bool Pretty);		
};