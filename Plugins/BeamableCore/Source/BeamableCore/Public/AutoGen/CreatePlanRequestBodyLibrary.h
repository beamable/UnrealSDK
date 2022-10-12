
#pragma once

#include "CoreMinimal.h"
#include "CreatePlanRequestBody.h"

#include "CreatePlanRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCreatePlanRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize CreatePlanRequestBody To JSON String")
	static FString CreatePlanRequestBodyToJsonString(const UCreatePlanRequestBody* Serializable, const bool Pretty);		
};