

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalContentLimits.h"

#include "OptionalContentLimitsLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalContentLimitsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalContentLimits MakeOptionalContentLimits(UContentLimits* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ContentLimits To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalContentLimits Conv_OptionalContentLimitsFromValue(UContentLimits* Value);
};
