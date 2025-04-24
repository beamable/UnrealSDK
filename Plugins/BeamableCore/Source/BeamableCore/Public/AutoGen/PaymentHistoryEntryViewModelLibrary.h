#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PaymentHistoryEntryViewModel.h"

#include "PaymentHistoryEntryViewModelLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPaymentHistoryEntryViewModelLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="PaymentHistoryEntryViewModel To JSON String")
	static FString PaymentHistoryEntryViewModelToJsonString(const UPaymentHistoryEntryViewModel* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make PaymentHistoryEntryViewModel", meta=(DefaultToSelf="Outer", AdvancedDisplay="Data, Timestamp, Outer", NativeMakeFunc))
	static UPaymentHistoryEntryViewModel* Make(FString Change, FOptionalString Data, FOptionalString Timestamp, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break PaymentHistoryEntryViewModel", meta=(NativeBreakFunc))
	static void Break(const UPaymentHistoryEntryViewModel* Serializable, FString& Change, FOptionalString& Data, FOptionalString& Timestamp);
};