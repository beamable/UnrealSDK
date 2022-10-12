

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfPlayerStatRequirement.h"

#include "OptionalArrayOfPlayerStatRequirementLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfPlayerStatRequirementLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfPlayerStatRequirement MakeOptionalArrayOfPlayerStatRequirement(TArray<UPlayerStatRequirement*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UPlayerStatRequirement*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfPlayerStatRequirement Conv_OptionalArrayOfPlayerStatRequirementFromValue(TArray<UPlayerStatRequirement*> Value);
};
