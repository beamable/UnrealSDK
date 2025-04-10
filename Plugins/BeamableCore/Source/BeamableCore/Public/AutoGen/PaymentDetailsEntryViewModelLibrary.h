#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PaymentDetailsEntryViewModel.h"

#include "PaymentDetailsEntryViewModelLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPaymentDetailsEntryViewModelLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="PaymentDetailsEntryViewModel To JSON String")
	static FString PaymentDetailsEntryViewModelToJsonString(const UPaymentDetailsEntryViewModel* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make PaymentDetailsEntryViewModel", meta=(DefaultToSelf="Outer", AdvancedDisplay="Subcategory, LocalPrice, Category, LocalCurrency, Outer", NativeMakeFunc))
	static UPaymentDetailsEntryViewModel* Make(FString Reference, FString Name, int32 Quantity, FString Sku, int32 Price, FString Gameplace, FString ProviderProductId, FOptionalString Subcategory, FOptionalString LocalPrice, FOptionalString Category, FOptionalString LocalCurrency, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break PaymentDetailsEntryViewModel", meta=(NativeBreakFunc))
	static void Break(const UPaymentDetailsEntryViewModel* Serializable, FString& Reference, FString& Name, int32& Quantity, FString& Sku, int32& Price, FString& Gameplace, FString& ProviderProductId, FOptionalString& Subcategory, FOptionalString& LocalPrice, FOptionalString& Category, FOptionalString& LocalCurrency);
};