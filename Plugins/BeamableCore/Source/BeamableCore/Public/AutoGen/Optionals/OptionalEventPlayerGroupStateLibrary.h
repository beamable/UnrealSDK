

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalEventPlayerGroupState.h"

#include "OptionalEventPlayerGroupStateLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalEventPlayerGroupStateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalEventPlayerGroupState MakeOptionalEventPlayerGroupState(UEventPlayerGroupState* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "EventPlayerGroupState To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalEventPlayerGroupState Conv_OptionalEventPlayerGroupStateFromValue(UEventPlayerGroupState* Value);
};
