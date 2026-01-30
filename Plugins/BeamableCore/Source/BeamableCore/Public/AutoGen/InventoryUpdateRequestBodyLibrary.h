#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/InventoryUpdateRequestBody.h"

#include "InventoryUpdateRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UInventoryUpdateRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Json", DisplayName="InventoryUpdateRequestBody To JSON String")
	static FString InventoryUpdateRequestBodyToJsonString(const UInventoryUpdateRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Make InventoryUpdateRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bApplyVipBonus, bIncludeDeltas, Transaction, Scopes, UpdateItems, NewItems, DeleteItems, Currencies, CurrencyProperties, Outer", NativeMakeFunc))
	static UInventoryUpdateRequestBody* Make(FOptionalBool bApplyVipBonus, FOptionalBool bIncludeDeltas, FOptionalString Transaction, FOptionalArrayOfString Scopes, FOptionalArrayOfItemUpdateRequestBody UpdateItems, FOptionalArrayOfItemCreateRequestBody NewItems, FOptionalArrayOfItemDeleteRequestBody DeleteItems, FOptionalMapOfInt64 Currencies, FOptionalMapOfArrayOfCurrencyProperty CurrencyProperties, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Break InventoryUpdateRequestBody", meta=(NativeBreakFunc))
	static void Break(const UInventoryUpdateRequestBody* Serializable, FOptionalBool& bApplyVipBonus, FOptionalBool& bIncludeDeltas, FOptionalString& Transaction, FOptionalArrayOfString& Scopes, FOptionalArrayOfItemUpdateRequestBody& UpdateItems, FOptionalArrayOfItemCreateRequestBody& NewItems, FOptionalArrayOfItemDeleteRequestBody& DeleteItems, FOptionalMapOfInt64& Currencies, FOptionalMapOfArrayOfCurrencyProperty& CurrencyProperties);
};