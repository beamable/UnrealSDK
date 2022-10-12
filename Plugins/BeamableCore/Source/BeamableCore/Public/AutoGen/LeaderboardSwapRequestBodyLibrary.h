
#pragma once

#include "CoreMinimal.h"
#include "LeaderboardSwapRequestBody.h"

#include "LeaderboardSwapRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULeaderboardSwapRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LeaderboardSwapRequestBody To JSON String")
	static FString LeaderboardSwapRequestBodyToJsonString(const ULeaderboardSwapRequestBody* Serializable, const bool Pretty);		
};