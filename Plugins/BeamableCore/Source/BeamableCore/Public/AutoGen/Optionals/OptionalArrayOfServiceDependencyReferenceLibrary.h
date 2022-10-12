

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfServiceDependencyReference.h"

#include "OptionalArrayOfServiceDependencyReferenceLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfServiceDependencyReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfServiceDependencyReference MakeOptionalArrayOfServiceDependencyReference(TArray<UServiceDependencyReference*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UServiceDependencyReference*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfServiceDependencyReference Conv_OptionalArrayOfServiceDependencyReferenceFromValue(TArray<UServiceDependencyReference*> Value);
};
