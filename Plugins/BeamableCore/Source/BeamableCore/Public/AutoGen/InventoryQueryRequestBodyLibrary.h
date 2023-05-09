#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/InventoryQueryRequestBody.h"

#include "InventoryQueryRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UInventoryQueryRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - InventoryQueryRequestBody To JSON String")
	static FString InventoryQueryRequestBodyToJsonString(const UInventoryQueryRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make InventoryQueryRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Scopes, Outer", NativeMakeFunc))
	static UInventoryQueryRequestBody* Make(FOptionalArrayOfString Scopes, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break InventoryQueryRequestBody", meta=(NativeBreakFunc))
	static void Break(const UInventoryQueryRequestBody* Serializable, FOptionalArrayOfString& Scopes);
};