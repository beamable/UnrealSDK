

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalMapOfString.h"

#include "OptionalMapOfStringLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalMapOfStringLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalMapOfString MakeOptionalMapOfString(TMap<FString, FString> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TMap<FString, FString> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalMapOfString Conv_OptionalMapOfStringFromValue(TMap<FString, FString> Value);
};
