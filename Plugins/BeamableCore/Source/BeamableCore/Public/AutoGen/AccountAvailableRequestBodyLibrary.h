
#pragma once

#include "CoreMinimal.h"
#include "AccountAvailableRequestBody.h"

#include "AccountAvailableRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAccountAvailableRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AccountAvailableRequestBody To JSON String")
	static FString AccountAvailableRequestBodyToJsonString(const UAccountAvailableRequestBody* Serializable, const bool Pretty);		
};