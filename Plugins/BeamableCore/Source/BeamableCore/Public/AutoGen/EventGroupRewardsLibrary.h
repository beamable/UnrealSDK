
#pragma once

#include "CoreMinimal.h"
#include "EventGroupRewards.h"

#include "EventGroupRewardsLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEventGroupRewardsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EventGroupRewards To JSON String")
	static FString EventGroupRewardsToJsonString(const UEventGroupRewards* Serializable, const bool Pretty);		
};