#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/InventoryQueryRequestBody.h"

#include "InventoryQueryRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UInventoryQueryRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Json", DisplayName="InventoryQueryRequestBody To JSON String")
	static FString InventoryQueryRequestBodyToJsonString(const UInventoryQueryRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Make InventoryQueryRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Scopes, Outer", NativeMakeFunc))
	static UInventoryQueryRequestBody* Make(FOptionalArrayOfString Scopes, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Break InventoryQueryRequestBody", meta=(NativeBreakFunc))
	static void Break(const UInventoryQueryRequestBody* Serializable, FOptionalArrayOfString& Scopes);
};