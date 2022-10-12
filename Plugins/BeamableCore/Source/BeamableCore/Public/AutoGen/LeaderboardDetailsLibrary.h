
#pragma once

#include "CoreMinimal.h"
#include "LeaderboardDetails.h"

#include "LeaderboardDetailsLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULeaderboardDetailsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LeaderboardDetails To JSON String")
	static FString LeaderboardDetailsToJsonString(const ULeaderboardDetails* Serializable, const bool Pretty);		
};