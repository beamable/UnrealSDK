
#pragma once

#include "CoreMinimal.h"
#include "CurrencyView.h"

#include "CurrencyViewLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCurrencyViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize CurrencyView To JSON String")
	static FString CurrencyViewToJsonString(const UCurrencyView* Serializable, const bool Pretty);		
};