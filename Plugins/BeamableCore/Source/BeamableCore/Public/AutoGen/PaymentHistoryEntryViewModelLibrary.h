
#pragma once

#include "CoreMinimal.h"
#include "PaymentHistoryEntryViewModel.h"

#include "PaymentHistoryEntryViewModelLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPaymentHistoryEntryViewModelLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PaymentHistoryEntryViewModel To JSON String")
	static FString PaymentHistoryEntryViewModelToJsonString(const UPaymentHistoryEntryViewModel* Serializable, const bool Pretty);		
};