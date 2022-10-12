
#pragma once

#include "CoreMinimal.h"
#include "LocalizedPriceMap.h"

#include "LocalizedPriceMapLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULocalizedPriceMapLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LocalizedPriceMap To JSON String")
	static FString LocalizedPriceMapToJsonString(const ULocalizedPriceMap* Serializable, const bool Pretty);		
};