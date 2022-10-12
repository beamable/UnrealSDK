
#pragma once

#include "CoreMinimal.h"
#include "Currency.h"

#include "CurrencyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCurrencyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize Currency To JSON String")
	static FString CurrencyToJsonString(const UCurrency* Serializable, const bool Pretty);		
};