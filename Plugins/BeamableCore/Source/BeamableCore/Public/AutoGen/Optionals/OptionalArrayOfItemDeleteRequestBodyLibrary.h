

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfItemDeleteRequestBody.h"

#include "OptionalArrayOfItemDeleteRequestBodyLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfItemDeleteRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfItemDeleteRequestBody MakeOptionalArrayOfItemDeleteRequestBody(TArray<UItemDeleteRequestBody*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UItemDeleteRequestBody*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfItemDeleteRequestBody Conv_OptionalArrayOfItemDeleteRequestBodyFromValue(TArray<UItemDeleteRequestBody*> Value);
};
