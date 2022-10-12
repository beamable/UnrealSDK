

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfItemCreateRequestBody.h"

#include "OptionalArrayOfItemCreateRequestBodyLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfItemCreateRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfItemCreateRequestBody MakeOptionalArrayOfItemCreateRequestBody(TArray<UItemCreateRequestBody*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UItemCreateRequestBody*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfItemCreateRequestBody Conv_OptionalArrayOfItemCreateRequestBodyFromValue(TArray<UItemCreateRequestBody*> Value);
};
