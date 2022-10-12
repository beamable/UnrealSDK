
#pragma once

#include "CoreMinimal.h"
#include "LeaderboardRemoveEntryRequestBody.h"

#include "LeaderboardRemoveEntryRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULeaderboardRemoveEntryRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LeaderboardRemoveEntryRequestBody To JSON String")
	static FString LeaderboardRemoveEntryRequestBodyToJsonString(const ULeaderboardRemoveEntryRequestBody* Serializable, const bool Pretty);		
};