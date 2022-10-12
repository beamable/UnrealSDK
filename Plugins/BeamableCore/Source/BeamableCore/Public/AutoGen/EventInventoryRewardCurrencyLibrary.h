
#pragma once

#include "CoreMinimal.h"
#include "EventInventoryRewardCurrency.h"

#include "EventInventoryRewardCurrencyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEventInventoryRewardCurrencyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EventInventoryRewardCurrency To JSON String")
	static FString EventInventoryRewardCurrencyToJsonString(const UEventInventoryRewardCurrency* Serializable, const bool Pretty);		
};