#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ItemGroup.h"

#include "ItemGroupLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UItemGroupLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Json", DisplayName="ItemGroup To JSON String")
	static FString ItemGroupToJsonString(const UItemGroup* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Make ItemGroup", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UItemGroup* Make(FString Id, TArray<UItem*> Items, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Break ItemGroup", meta=(NativeBreakFunc))
	static void Break(const UItemGroup* Serializable, FString& Id, TArray<UItem*>& Items);
};