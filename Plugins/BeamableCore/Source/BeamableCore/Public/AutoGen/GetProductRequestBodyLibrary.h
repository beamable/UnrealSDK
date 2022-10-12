
#pragma once

#include "CoreMinimal.h"
#include "GetProductRequestBody.h"

#include "GetProductRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetProductRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetProductRequestBody To JSON String")
	static FString GetProductRequestBodyToJsonString(const UGetProductRequestBody* Serializable, const bool Pretty);		
};