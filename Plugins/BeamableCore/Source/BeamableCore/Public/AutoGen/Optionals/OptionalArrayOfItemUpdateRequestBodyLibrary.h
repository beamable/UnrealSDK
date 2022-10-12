

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfItemUpdateRequestBody.h"

#include "OptionalArrayOfItemUpdateRequestBodyLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfItemUpdateRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfItemUpdateRequestBody MakeOptionalArrayOfItemUpdateRequestBody(TArray<UItemUpdateRequestBody*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UItemUpdateRequestBody*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfItemUpdateRequestBody Conv_OptionalArrayOfItemUpdateRequestBodyFromValue(TArray<UItemUpdateRequestBody*> Value);
};
