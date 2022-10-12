
#pragma once

#include "CoreMinimal.h"
#include "LeaderboardAddRequestBody.h"

#include "LeaderboardAddRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULeaderboardAddRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LeaderboardAddRequestBody To JSON String")
	static FString LeaderboardAddRequestBodyToJsonString(const ULeaderboardAddRequestBody* Serializable, const bool Pretty);		
};