#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/PaymentDetailsEntryViewModel.h"

#include "PaymentDetailsEntryViewModelLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPaymentDetailsEntryViewModelLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - PaymentDetailsEntryViewModel To JSON String")
	static FString PaymentDetailsEntryViewModelToJsonString(const UPaymentDetailsEntryViewModel* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make PaymentDetailsEntryViewModel", meta=(DefaultToSelf="Outer", AdvancedDisplay="Subcategory, LocalPrice, Category, LocalCurrency, Outer", NativeMakeFunc))
	static UPaymentDetailsEntryViewModel* Make(FString Reference, FString Name, int32 Quantity, FString Sku, int32 Price, FString Gameplace, FString ProviderProductId, FOptionalString Subcategory, FOptionalString LocalPrice, FOptionalString Category, FOptionalString LocalCurrency, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break PaymentDetailsEntryViewModel", meta=(NativeBreakFunc))
	static void Break(const UPaymentDetailsEntryViewModel* Serializable, FString& Reference, FString& Name, int32& Quantity, FString& Sku, int32& Price, FString& Gameplace, FString& ProviderProductId, FOptionalString& Subcategory, FOptionalString& LocalPrice, FOptionalString& Category, FOptionalString& LocalCurrency);
};