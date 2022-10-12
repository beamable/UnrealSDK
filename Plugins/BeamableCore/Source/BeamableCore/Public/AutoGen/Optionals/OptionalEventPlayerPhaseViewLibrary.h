

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalEventPlayerPhaseView.h"

#include "OptionalEventPlayerPhaseViewLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalEventPlayerPhaseViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalEventPlayerPhaseView MakeOptionalEventPlayerPhaseView(UEventPlayerPhaseView* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "EventPlayerPhaseView To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalEventPlayerPhaseView Conv_OptionalEventPlayerPhaseViewFromValue(UEventPlayerPhaseView* Value);
};
