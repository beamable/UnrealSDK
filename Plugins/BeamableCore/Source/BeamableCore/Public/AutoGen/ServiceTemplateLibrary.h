
#pragma once

#include "CoreMinimal.h"
#include "ServiceTemplate.h"

#include "ServiceTemplateLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UServiceTemplateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ServiceTemplate To JSON String")
	static FString ServiceTemplateToJsonString(const UServiceTemplate* Serializable, const bool Pretty);		
};