
#pragma once

#include "CoreMinimal.h"
#include "LeaderboardMembershipResponse.h"

#include "LeaderboardMembershipResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULeaderboardMembershipResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LeaderboardMembershipResponse To JSON String")
	static FString LeaderboardMembershipResponseToJsonString(const ULeaderboardMembershipResponse* Serializable, const bool Pretty);		
};