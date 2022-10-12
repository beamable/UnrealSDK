
#pragma once

#include "CoreMinimal.h"
#include "LeaderboardAssignmentInfo.h"

#include "LeaderboardAssignmentInfoLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULeaderboardAssignmentInfoLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LeaderboardAssignmentInfo To JSON String")
	static FString LeaderboardAssignmentInfoToJsonString(const ULeaderboardAssignmentInfo* Serializable, const bool Pretty);		
};