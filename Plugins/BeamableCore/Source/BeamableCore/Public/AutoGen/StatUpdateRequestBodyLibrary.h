
#pragma once

#include "CoreMinimal.h"
#include "StatUpdateRequestBody.h"

#include "StatUpdateRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UStatUpdateRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize StatUpdateRequestBody To JSON String")
	static FString StatUpdateRequestBodyToJsonString(const UStatUpdateRequestBody* Serializable, const bool Pretty);		
};