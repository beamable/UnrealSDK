
#pragma once

#include "CoreMinimal.h"
#include "LeaderboardGetMatchRequestBody.h"

#include "LeaderboardGetMatchRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULeaderboardGetMatchRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LeaderboardGetMatchRequestBody To JSON String")
	static FString LeaderboardGetMatchRequestBodyToJsonString(const ULeaderboardGetMatchRequestBody* Serializable, const bool Pretty);		
};