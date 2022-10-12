
#pragma once

#include "CoreMinimal.h"
#include "SaveSKUsRequestBody.h"

#include "SaveSKUsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API USaveSKUsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize SaveSKUsRequestBody To JSON String")
	static FString SaveSKUsRequestBodyToJsonString(const USaveSKUsRequestBody* Serializable, const bool Pretty);		
};