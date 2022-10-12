
#pragma once

#include "CoreMinimal.h"
#include "CurrencyChangeReward.h"

#include "CurrencyChangeRewardLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCurrencyChangeRewardLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize CurrencyChangeReward To JSON String")
	static FString CurrencyChangeRewardToJsonString(const UCurrencyChangeReward* Serializable, const bool Pretty);		
};