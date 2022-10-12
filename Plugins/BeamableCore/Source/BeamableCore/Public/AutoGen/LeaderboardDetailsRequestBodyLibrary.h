
#pragma once

#include "CoreMinimal.h"
#include "LeaderboardDetailsRequestBody.h"

#include "LeaderboardDetailsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULeaderboardDetailsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LeaderboardDetailsRequestBody To JSON String")
	static FString LeaderboardDetailsRequestBodyToJsonString(const ULeaderboardDetailsRequestBody* Serializable, const bool Pretty);		
};