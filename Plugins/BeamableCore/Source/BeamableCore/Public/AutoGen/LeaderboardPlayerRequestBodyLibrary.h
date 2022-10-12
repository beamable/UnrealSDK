
#pragma once

#include "CoreMinimal.h"
#include "LeaderboardPlayerRequestBody.h"

#include "LeaderboardPlayerRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULeaderboardPlayerRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LeaderboardPlayerRequestBody To JSON String")
	static FString LeaderboardPlayerRequestBodyToJsonString(const ULeaderboardPlayerRequestBody* Serializable, const bool Pretty);		
};