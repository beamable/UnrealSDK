

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalEventPhaseRuntime.h"

#include "OptionalEventPhaseRuntimeLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalEventPhaseRuntimeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalEventPhaseRuntime MakeOptionalEventPhaseRuntime(UEventPhaseRuntime* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "EventPhaseRuntime To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalEventPhaseRuntime Conv_OptionalEventPhaseRuntimeFromValue(UEventPhaseRuntime* Value);
};
