
#pragma once

#include "CoreMinimal.h"
#include "CompletePurchaseRequestBody.h"

#include "CompletePurchaseRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCompletePurchaseRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize CompletePurchaseRequestBody To JSON String")
	static FString CompletePurchaseRequestBodyToJsonString(const UCompletePurchaseRequestBody* Serializable, const bool Pretty);		
};