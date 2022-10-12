

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalInventoryProxySettings.h"

#include "OptionalInventoryProxySettingsLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalInventoryProxySettingsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalInventoryProxySettings MakeOptionalInventoryProxySettings(UInventoryProxySettings* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "InventoryProxySettings To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalInventoryProxySettings Conv_OptionalInventoryProxySettingsFromValue(UInventoryProxySettings* Value);
};
