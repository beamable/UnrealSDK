#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/InventoryGetRequestBody.h"

#include "InventoryGetRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UInventoryGetRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Json", DisplayName="InventoryGetRequestBody To JSON String")
	static FString InventoryGetRequestBodyToJsonString(const UInventoryGetRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Make InventoryGetRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Scope, Outer", NativeMakeFunc))
	static UInventoryGetRequestBody* Make(FOptionalString Scope, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Break InventoryGetRequestBody", meta=(NativeBreakFunc))
	static void Break(const UInventoryGetRequestBody* Serializable, FOptionalString& Scope);
};