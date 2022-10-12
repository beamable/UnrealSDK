
#pragma once

#include "CoreMinimal.h"
#include "PlayerReward.h"

#include "PlayerRewardLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPlayerRewardLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PlayerReward To JSON String")
	static FString PlayerRewardToJsonString(const UPlayerReward* Serializable, const bool Pretty);		
};