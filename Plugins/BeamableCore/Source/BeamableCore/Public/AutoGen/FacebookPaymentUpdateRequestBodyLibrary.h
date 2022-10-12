
#pragma once

#include "CoreMinimal.h"
#include "FacebookPaymentUpdateRequestBody.h"

#include "FacebookPaymentUpdateRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UFacebookPaymentUpdateRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize FacebookPaymentUpdateRequestBody To JSON String")
	static FString FacebookPaymentUpdateRequestBodyToJsonString(const UFacebookPaymentUpdateRequestBody* Serializable, const bool Pretty);		
};