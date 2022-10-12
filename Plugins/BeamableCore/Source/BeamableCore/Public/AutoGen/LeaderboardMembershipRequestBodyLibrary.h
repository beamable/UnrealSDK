
#pragma once

#include "CoreMinimal.h"
#include "LeaderboardMembershipRequestBody.h"

#include "LeaderboardMembershipRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULeaderboardMembershipRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LeaderboardMembershipRequestBody To JSON String")
	static FString LeaderboardMembershipRequestBodyToJsonString(const ULeaderboardMembershipRequestBody* Serializable, const bool Pretty);		
};