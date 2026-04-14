#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/InventoryUpdateResponse.h"

#include "InventoryUpdateResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UInventoryUpdateResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Json", DisplayName="InventoryUpdateResponse To JSON String")
	static FString InventoryUpdateResponseToJsonString(const UInventoryUpdateResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Make InventoryUpdateResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Deltas, Outer", NativeMakeFunc))
	static UInventoryUpdateResponse* Make(FString Result, TMap<FString, FString> Data, FOptionalInventoryUpdateDelta Deltas, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Break InventoryUpdateResponse", meta=(NativeBreakFunc))
	static void Break(const UInventoryUpdateResponse* Serializable, FString& Result, TMap<FString, FString>& Data, FOptionalInventoryUpdateDelta& Deltas);
};