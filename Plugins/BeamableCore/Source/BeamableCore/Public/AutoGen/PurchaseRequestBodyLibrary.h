
#pragma once

#include "CoreMinimal.h"
#include "PurchaseRequestBody.h"

#include "PurchaseRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPurchaseRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PurchaseRequestBody To JSON String")
	static FString PurchaseRequestBodyToJsonString(const UPurchaseRequestBody* Serializable, const bool Pretty);		
};