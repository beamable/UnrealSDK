
#pragma once

#include "CoreMinimal.h"
#include "PaymentResultResponse.h"

#include "PaymentResultResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPaymentResultResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PaymentResultResponse To JSON String")
	static FString PaymentResultResponseToJsonString(const UPaymentResultResponse* Serializable, const bool Pretty);		
};