

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfEventPhaseTime.h"

#include "OptionalArrayOfEventPhaseTimeLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfEventPhaseTimeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfEventPhaseTime MakeOptionalArrayOfEventPhaseTime(TArray<UEventPhaseTime*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UEventPhaseTime*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfEventPhaseTime Conv_OptionalArrayOfEventPhaseTimeFromValue(TArray<UEventPhaseTime*> Value);
};
