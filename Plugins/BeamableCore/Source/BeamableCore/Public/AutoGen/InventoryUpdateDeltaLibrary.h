#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/InventoryUpdateDelta.h"

#include "InventoryUpdateDeltaLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UInventoryUpdateDeltaLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Json", DisplayName="InventoryUpdateDelta To JSON String")
	static FString InventoryUpdateDeltaToJsonString(const UInventoryUpdateDelta* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Make InventoryUpdateDelta", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UInventoryUpdateDelta* Make(UItemDeltas* Items, TMap<FString, UCurrencyDelta*> Currencies, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Break InventoryUpdateDelta", meta=(NativeBreakFunc))
	static void Break(const UInventoryUpdateDelta* Serializable, UItemDeltas*& Items, TMap<FString, UCurrencyDelta*>& Currencies);
};