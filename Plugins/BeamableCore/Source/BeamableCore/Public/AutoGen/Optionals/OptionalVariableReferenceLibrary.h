

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalVariableReference.h"

#include "OptionalVariableReferenceLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalVariableReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalVariableReference MakeOptionalVariableReference(UVariableReference* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "VariableReference To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalVariableReference Conv_OptionalVariableReferenceFromValue(UVariableReference* Value);
};
