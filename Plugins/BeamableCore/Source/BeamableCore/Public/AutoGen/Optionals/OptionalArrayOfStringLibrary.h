

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfString.h"

#include "OptionalArrayOfStringLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfStringLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfString MakeOptionalArrayOfString(TArray<FString> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<FString> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfString Conv_OptionalArrayOfStringFromValue(TArray<FString> Value);
};
