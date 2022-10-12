
#pragma once

#include "CoreMinimal.h"
#include "GetOrderInfoRequestBody.h"

#include "GetOrderInfoRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetOrderInfoRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetOrderInfoRequestBody To JSON String")
	static FString GetOrderInfoRequestBodyToJsonString(const UGetOrderInfoRequestBody* Serializable, const bool Pretty);		
};