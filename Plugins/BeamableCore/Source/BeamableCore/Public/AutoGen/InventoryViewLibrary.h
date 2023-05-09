#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/InventoryView.h"

#include "InventoryViewLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UInventoryViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - InventoryView To JSON String")
	static FString InventoryViewToJsonString(const UInventoryView* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make InventoryView", meta=(DefaultToSelf="Outer", AdvancedDisplay="Scope, Outer", NativeMakeFunc))
	static UInventoryView* Make(TArray<UCurrencyView*> Currencies, TArray<UItemGroup*> Items, FOptionalString Scope, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break InventoryView", meta=(NativeBreakFunc))
	static void Break(const UInventoryView* Serializable, TArray<UCurrencyView*>& Currencies, TArray<UItemGroup*>& Items, FOptionalString& Scope);
};