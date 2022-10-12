
#pragma once

#include "CoreMinimal.h"
#include "EventInventoryRewardItem.h"

#include "EventInventoryRewardItemLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEventInventoryRewardItemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EventInventoryRewardItem To JSON String")
	static FString EventInventoryRewardItemToJsonString(const UEventInventoryRewardItem* Serializable, const bool Pretty);		
};