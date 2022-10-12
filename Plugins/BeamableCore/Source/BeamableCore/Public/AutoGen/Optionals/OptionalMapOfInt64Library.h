

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalMapOfInt64.h"

#include "OptionalMapOfInt64Library.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalMapOfInt64Library : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalMapOfInt64 MakeOptionalMapOfInt64(TMap<FString, int64> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TMap<FString, int64> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalMapOfInt64 Conv_OptionalMapOfInt64FromValue(TMap<FString, int64> Value);
};
