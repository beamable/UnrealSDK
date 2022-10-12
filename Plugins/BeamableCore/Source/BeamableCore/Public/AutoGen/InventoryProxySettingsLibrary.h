
#pragma once

#include "CoreMinimal.h"
#include "InventoryProxySettings.h"

#include "InventoryProxySettingsLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UInventoryProxySettingsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize InventoryProxySettings To JSON String")
	static FString InventoryProxySettingsToJsonString(const UInventoryProxySettings* Serializable, const bool Pretty);		
};