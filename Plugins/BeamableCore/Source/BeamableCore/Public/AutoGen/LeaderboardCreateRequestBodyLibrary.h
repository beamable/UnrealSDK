
#pragma once

#include "CoreMinimal.h"
#include "LeaderboardCreateRequestBody.h"

#include "LeaderboardCreateRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULeaderboardCreateRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LeaderboardCreateRequestBody To JSON String")
	static FString LeaderboardCreateRequestBodyToJsonString(const ULeaderboardCreateRequestBody* Serializable, const bool Pretty);		
};