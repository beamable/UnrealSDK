#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ItemDeltas.h"

#include "ItemDeltasLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UItemDeltasLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Json", DisplayName="ItemDeltas To JSON String")
	static FString ItemDeltasToJsonString(const UItemDeltas* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Make ItemDeltas", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UItemDeltas* Make(TArray<UItemPropertiesDelta*> Created, TArray<UItemPropertiesDelta*> Updated, TArray<UItemPropertiesDelta*> Deleted, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Break ItemDeltas", meta=(NativeBreakFunc))
	static void Break(const UItemDeltas* Serializable, TArray<UItemPropertiesDelta*>& Created, TArray<UItemPropertiesDelta*>& Updated, TArray<UItemPropertiesDelta*>& Deleted);
};