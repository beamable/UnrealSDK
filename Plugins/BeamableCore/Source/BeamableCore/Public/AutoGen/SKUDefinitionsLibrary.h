
#pragma once

#include "CoreMinimal.h"
#include "SKUDefinitions.h"

#include "SKUDefinitionsLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API USKUDefinitionsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize SKUDefinitions To JSON String")
	static FString SKUDefinitionsToJsonString(const USKUDefinitions* Serializable, const bool Pretty);		
};