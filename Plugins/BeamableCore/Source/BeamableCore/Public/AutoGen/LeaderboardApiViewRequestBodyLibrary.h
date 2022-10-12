
#pragma once

#include "CoreMinimal.h"
#include "LeaderboardApiViewRequestBody.h"

#include "LeaderboardApiViewRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULeaderboardApiViewRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LeaderboardApiViewRequestBody To JSON String")
	static FString LeaderboardApiViewRequestBodyToJsonString(const ULeaderboardApiViewRequestBody* Serializable, const bool Pretty);		
};