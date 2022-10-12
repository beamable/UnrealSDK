
#pragma once

#include "CoreMinimal.h"
#include "ItemProperty.h"

#include "ItemPropertyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UItemPropertyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ItemProperty To JSON String")
	static FString ItemPropertyToJsonString(const UItemProperty* Serializable, const bool Pretty);		
};