

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfInFlightMessage.h"

#include "OptionalArrayOfInFlightMessageLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfInFlightMessageLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfInFlightMessage MakeOptionalArrayOfInFlightMessage(TArray<UInFlightMessage*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UInFlightMessage*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfInFlightMessage Conv_OptionalArrayOfInFlightMessageFromValue(TArray<UInFlightMessage*> Value);
};
