
#pragma once

#include "CoreMinimal.h"
#include "GetPricesRequestBody.h"

#include "GetPricesRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetPricesRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetPricesRequestBody To JSON String")
	static FString GetPricesRequestBodyToJsonString(const UGetPricesRequestBody* Serializable, const bool Pretty);		
};