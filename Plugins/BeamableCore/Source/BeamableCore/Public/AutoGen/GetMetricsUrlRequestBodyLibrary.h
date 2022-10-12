
#pragma once

#include "CoreMinimal.h"
#include "GetMetricsUrlRequestBody.h"

#include "GetMetricsUrlRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetMetricsUrlRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetMetricsUrlRequestBody To JSON String")
	static FString GetMetricsUrlRequestBodyToJsonString(const UGetMetricsUrlRequestBody* Serializable, const bool Pretty);		
};