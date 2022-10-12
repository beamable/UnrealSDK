

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalBeamoLimits.h"

#include "OptionalBeamoLimitsLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalBeamoLimitsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalBeamoLimits MakeOptionalBeamoLimits(UBeamoLimits* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "BeamoLimits To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalBeamoLimits Conv_OptionalBeamoLimitsFromValue(UBeamoLimits* Value);
};
