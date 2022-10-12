
#pragma once

#include "CoreMinimal.h"
#include "PaymentDetailsEntryViewModel.h"

#include "PaymentDetailsEntryViewModelLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPaymentDetailsEntryViewModelLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PaymentDetailsEntryViewModel To JSON String")
	static FString PaymentDetailsEntryViewModelToJsonString(const UPaymentDetailsEntryViewModel* Serializable, const bool Pretty);		
};