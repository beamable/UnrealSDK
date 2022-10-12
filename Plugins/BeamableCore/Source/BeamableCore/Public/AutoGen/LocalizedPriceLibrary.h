
#pragma once

#include "CoreMinimal.h"
#include "LocalizedPrice.h"

#include "LocalizedPriceLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULocalizedPriceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LocalizedPrice To JSON String")
	static FString LocalizedPriceToJsonString(const ULocalizedPrice* Serializable, const bool Pretty);		
};