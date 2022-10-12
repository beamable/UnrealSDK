

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalBool.h"

#include "OptionalBoolLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalBoolLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalBool MakeOptionalBool(bool Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Bool To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalBool Conv_OptionalBoolFromValue(bool Value);
};
