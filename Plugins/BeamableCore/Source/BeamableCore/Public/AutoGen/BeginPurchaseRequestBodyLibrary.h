
#pragma once

#include "CoreMinimal.h"
#include "BeginPurchaseRequestBody.h"

#include "BeginPurchaseRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UBeginPurchaseRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize BeginPurchaseRequestBody To JSON String")
	static FString BeginPurchaseRequestBodyToJsonString(const UBeginPurchaseRequestBody* Serializable, const bool Pretty);		
};