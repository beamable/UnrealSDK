#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/InventoryUpdateRequestBody.h"

#include "InventoryUpdateRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UInventoryUpdateRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - InventoryUpdateRequestBody To JSON String")
	static FString InventoryUpdateRequestBodyToJsonString(const UInventoryUpdateRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make InventoryUpdateRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bApplyVipBonus, Transaction, UpdateItems, NewItems, DeleteItems, Currencies, CurrencyProperties, Outer", NativeMakeFunc))
	static UInventoryUpdateRequestBody* Make(bool bEmpty, TArray<FString> CurrencyContentIds, TArray<FString> ItemContentIds, FOptionalBool bApplyVipBonus, FOptionalString Transaction, FOptionalArrayOfItemUpdateRequestBody UpdateItems, FOptionalArrayOfItemCreateRequestBody NewItems, FOptionalArrayOfItemDeleteRequestBody DeleteItems, FOptionalMapOfInt64 Currencies, FOptionalMapOfArrayOfCurrencyProperty CurrencyProperties, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break InventoryUpdateRequestBody", meta=(NativeBreakFunc))
	static void Break(const UInventoryUpdateRequestBody* Serializable, bool& bEmpty, TArray<FString>& CurrencyContentIds, TArray<FString>& ItemContentIds, FOptionalBool& bApplyVipBonus, FOptionalString& Transaction, FOptionalArrayOfItemUpdateRequestBody& UpdateItems, FOptionalArrayOfItemCreateRequestBody& NewItems, FOptionalArrayOfItemDeleteRequestBody& DeleteItems, FOptionalMapOfInt64& Currencies, FOptionalMapOfArrayOfCurrencyProperty& CurrencyProperties);
};