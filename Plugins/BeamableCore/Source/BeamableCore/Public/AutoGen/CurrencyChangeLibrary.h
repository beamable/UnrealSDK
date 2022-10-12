
#pragma once

#include "CoreMinimal.h"
#include "CurrencyChange.h"

#include "CurrencyChangeLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCurrencyChangeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize CurrencyChange To JSON String")
	static FString CurrencyChangeToJsonString(const UCurrencyChange* Serializable, const bool Pretty);		
};