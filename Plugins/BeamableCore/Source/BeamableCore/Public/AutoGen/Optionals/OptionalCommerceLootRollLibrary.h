

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalCommerceLootRoll.h"

#include "OptionalCommerceLootRollLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalCommerceLootRollLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalCommerceLootRoll MakeOptionalCommerceLootRoll(UCommerceLootRoll* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "CommerceLootRoll To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalCommerceLootRoll Conv_OptionalCommerceLootRollFromValue(UCommerceLootRoll* Value);
};
