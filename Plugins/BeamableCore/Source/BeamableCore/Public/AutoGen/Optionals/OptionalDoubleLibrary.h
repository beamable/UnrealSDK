

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalDouble.h"

#include "OptionalDoubleLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalDoubleLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalDouble MakeOptionalDouble(double Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Double To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalDouble Conv_OptionalDoubleFromValue(double Value);
};
