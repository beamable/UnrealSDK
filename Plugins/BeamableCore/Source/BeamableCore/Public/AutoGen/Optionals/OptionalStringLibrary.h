

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "OptionalStringLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalStringLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalString MakeOptionalString(FString Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "String To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalString Conv_OptionalStringFromValue(FString Value);
};
