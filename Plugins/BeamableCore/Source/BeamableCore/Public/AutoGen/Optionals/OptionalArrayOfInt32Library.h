

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfInt32.h"

#include "OptionalArrayOfInt32Library.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfInt32Library : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfInt32 MakeOptionalArrayOfInt32(TArray<int32> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<int32> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfInt32 Conv_OptionalArrayOfInt32FromValue(TArray<int32> Value);
};
