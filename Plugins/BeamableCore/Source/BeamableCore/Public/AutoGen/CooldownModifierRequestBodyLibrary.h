
#pragma once

#include "CoreMinimal.h"
#include "CooldownModifierRequestBody.h"

#include "CooldownModifierRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCooldownModifierRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize CooldownModifierRequestBody To JSON String")
	static FString CooldownModifierRequestBodyToJsonString(const UCooldownModifierRequestBody* Serializable, const bool Pretty);		
};