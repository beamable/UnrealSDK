
#pragma once

#include "CoreMinimal.h"
#include "PaymentAuditEntryViewModel.h"

#include "PaymentAuditEntryViewModelLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPaymentAuditEntryViewModelLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PaymentAuditEntryViewModel To JSON String")
	static FString PaymentAuditEntryViewModelToJsonString(const UPaymentAuditEntryViewModel* Serializable, const bool Pretty);		
};