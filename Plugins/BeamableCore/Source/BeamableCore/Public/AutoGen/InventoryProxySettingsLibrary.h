
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/InventoryProxySettings.h"

#include "InventoryProxySettingsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UInventoryProxySettingsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - InventoryProxySettings To JSON String")
	static FString InventoryProxySettingsToJsonString(const UInventoryProxySettings* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make InventoryProxySettings", meta=(DefaultToSelf="Outer", AdvancedDisplay="Namespace, Outer", NativeMakeFunc))
	static UInventoryProxySettings* Make(FString Service, FOptionalString Namespace, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break InventoryProxySettings", meta=(NativeBreakFunc))
	static void Break(const UInventoryProxySettings* Serializable, FString& Service, FOptionalString& Namespace);
};