
#pragma once

#include "CoreMinimal.h"
#include "CurrencyProperty.h"

#include "CurrencyPropertyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCurrencyPropertyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize CurrencyProperty To JSON String")
	static FString CurrencyPropertyToJsonString(const UCurrencyProperty* Serializable, const bool Pretty);		
};