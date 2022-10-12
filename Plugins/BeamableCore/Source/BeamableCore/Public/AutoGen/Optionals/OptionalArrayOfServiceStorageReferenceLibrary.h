

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfServiceStorageReference.h"

#include "OptionalArrayOfServiceStorageReferenceLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfServiceStorageReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfServiceStorageReference MakeOptionalArrayOfServiceStorageReference(TArray<UServiceStorageReference*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UServiceStorageReference*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfServiceStorageReference Conv_OptionalArrayOfServiceStorageReferenceFromValue(TArray<UServiceStorageReference*> Value);
};
