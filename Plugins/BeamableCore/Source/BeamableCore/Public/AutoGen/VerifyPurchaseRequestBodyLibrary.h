
#pragma once

#include "CoreMinimal.h"
#include "VerifyPurchaseRequestBody.h"

#include "VerifyPurchaseRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UVerifyPurchaseRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize VerifyPurchaseRequestBody To JSON String")
	static FString VerifyPurchaseRequestBodyToJsonString(const UVerifyPurchaseRequestBody* Serializable, const bool Pretty);		
};