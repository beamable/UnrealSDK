
#pragma once

#include "CoreMinimal.h"
#include "SearchExtendedRequestBody.h"

#include "SearchExtendedRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API USearchExtendedRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize SearchExtendedRequestBody To JSON String")
	static FString SearchExtendedRequestBodyToJsonString(const USearchExtendedRequestBody* Serializable, const bool Pretty);		
};