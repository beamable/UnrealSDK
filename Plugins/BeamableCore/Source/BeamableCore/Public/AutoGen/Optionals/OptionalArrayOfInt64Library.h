

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfInt64.h"

#include "OptionalArrayOfInt64Library.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfInt64Library : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfInt64 MakeOptionalArrayOfInt64(TArray<int64> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<int64> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfInt64 Conv_OptionalArrayOfInt64FromValue(TArray<int64> Value);
};
