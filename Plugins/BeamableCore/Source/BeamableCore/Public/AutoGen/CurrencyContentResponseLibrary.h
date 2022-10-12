
#pragma once

#include "CoreMinimal.h"
#include "CurrencyContentResponse.h"

#include "CurrencyContentResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCurrencyContentResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize CurrencyContentResponse To JSON String")
	static FString CurrencyContentResponseToJsonString(const UCurrencyContentResponse* Serializable, const bool Pretty);		
};