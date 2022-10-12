
#pragma once

#include "CoreMinimal.h"
#include "SKU.h"

#include "SKULibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API USKULibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize SKU To JSON String")
	static FString SKUToJsonString(const USKU* Serializable, const bool Pretty);		
};