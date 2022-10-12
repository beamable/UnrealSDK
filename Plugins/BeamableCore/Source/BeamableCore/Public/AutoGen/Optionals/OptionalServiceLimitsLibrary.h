

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalServiceLimits.h"

#include "OptionalServiceLimitsLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalServiceLimitsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalServiceLimits MakeOptionalServiceLimits(UServiceLimits* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ServiceLimits To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalServiceLimits Conv_OptionalServiceLimitsFromValue(UServiceLimits* Value);
};
