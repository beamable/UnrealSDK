

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfObjectRequestBody.h"

#include "OptionalArrayOfObjectRequestBodyLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfObjectRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfObjectRequestBody MakeOptionalArrayOfObjectRequestBody(TArray<UObjectRequestBody*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UObjectRequestBody*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfObjectRequestBody Conv_OptionalArrayOfObjectRequestBodyFromValue(TArray<UObjectRequestBody*> Value);
};
