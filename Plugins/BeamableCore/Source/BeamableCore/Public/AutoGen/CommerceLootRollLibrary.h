
#pragma once

#include "CoreMinimal.h"
#include "CommerceLootRoll.h"

#include "CommerceLootRollLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCommerceLootRollLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize CommerceLootRoll To JSON String")
	static FString CommerceLootRollToJsonString(const UCommerceLootRoll* Serializable, const bool Pretty);		
};