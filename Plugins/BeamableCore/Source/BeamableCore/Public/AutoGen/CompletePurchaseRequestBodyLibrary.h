#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CompletePurchaseRequestBody.h"

#include "CompletePurchaseRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCompletePurchaseRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Json", DisplayName="CompletePurchaseRequestBody To JSON String")
	static FString CompletePurchaseRequestBodyToJsonString(const UCompletePurchaseRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make CompletePurchaseRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCompletePurchaseRequestBody* Make(int64 Txid, FString Receipt, FString PriceInLocalCurrency, FString IsoCurrencySymbol, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Break CompletePurchaseRequestBody", meta=(NativeBreakFunc))
	static void Break(const UCompletePurchaseRequestBody* Serializable, int64& Txid, FString& Receipt, FString& PriceInLocalCurrency, FString& IsoCurrencySymbol);
};