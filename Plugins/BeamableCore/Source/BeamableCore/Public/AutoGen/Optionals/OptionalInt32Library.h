

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalInt32.h"

#include "OptionalInt32Library.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalInt32Library : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalInt32 MakeOptionalInt32(int32 Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Int32 To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalInt32 Conv_OptionalInt32FromValue(int32 Value);
};
