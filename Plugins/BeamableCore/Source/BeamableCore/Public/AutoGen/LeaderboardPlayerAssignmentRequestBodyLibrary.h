
#pragma once

#include "CoreMinimal.h"
#include "LeaderboardPlayerAssignmentRequestBody.h"

#include "LeaderboardPlayerAssignmentRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULeaderboardPlayerAssignmentRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LeaderboardPlayerAssignmentRequestBody To JSON String")
	static FString LeaderboardPlayerAssignmentRequestBodyToJsonString(const ULeaderboardPlayerAssignmentRequestBody* Serializable, const bool Pretty);		
};