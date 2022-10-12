
#pragma once

#include "CoreMinimal.h"
#include "EventInventoryPendingRewards.h"

#include "EventInventoryPendingRewardsLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEventInventoryPendingRewardsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EventInventoryPendingRewards To JSON String")
	static FString EventInventoryPendingRewardsToJsonString(const UEventInventoryPendingRewards* Serializable, const bool Pretty);		
};