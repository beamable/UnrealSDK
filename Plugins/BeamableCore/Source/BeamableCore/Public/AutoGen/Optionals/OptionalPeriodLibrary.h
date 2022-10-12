

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalPeriod.h"

#include "OptionalPeriodLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalPeriodLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalPeriod MakeOptionalPeriod(UPeriod* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Period To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalPeriod Conv_OptionalPeriodFromValue(UPeriod* Value);
};
