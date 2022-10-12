
#pragma once

#include "CoreMinimal.h"
#include "CancelPurchaseRequestBody.h"

#include "CancelPurchaseRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCancelPurchaseRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize CancelPurchaseRequestBody To JSON String")
	static FString CancelPurchaseRequestBodyToJsonString(const UCancelPurchaseRequestBody* Serializable, const bool Pretty);		
};