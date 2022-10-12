
#pragma once

#include "CoreMinimal.h"
#include "Price.h"

#include "PriceLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPriceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize Price To JSON String")
	static FString PriceToJsonString(const UPrice* Serializable, const bool Pretty);		
};