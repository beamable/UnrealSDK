#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/TransactionDetails.h"

#include "TransactionDetailsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTransactionDetailsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Payment|Utils|Json", DisplayName="TransactionDetails To JSON String")
	static FString TransactionDetailsToJsonString(const UTransactionDetails* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Payment|Utils|Make/Break", DisplayName="Make TransactionDetails", meta=(DefaultToSelf="Outer", AdvancedDisplay="Quantity, Name, Reference, GamePlace, Category, Subcategory, LocalCurrency, LocalPrice, Outer", NativeMakeFunc))
	static UTransactionDetails* Make(int32 PriceCents, FString Sku, FString ProviderProductId, FOptionalInt32 Quantity, FOptionalString Name, FOptionalString Reference, FOptionalString GamePlace, FOptionalString Category, FOptionalString Subcategory, FOptionalString LocalCurrency, FOptionalString LocalPrice, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Payment|Utils|Make/Break", DisplayName="Break TransactionDetails", meta=(NativeBreakFunc))
	static void Break(const UTransactionDetails* Serializable, int32& PriceCents, FString& Sku, FString& ProviderProductId, FOptionalInt32& Quantity, FOptionalString& Name, FOptionalString& Reference, FOptionalString& GamePlace, FOptionalString& Category, FOptionalString& Subcategory, FOptionalString& LocalCurrency, FOptionalString& LocalPrice);
};