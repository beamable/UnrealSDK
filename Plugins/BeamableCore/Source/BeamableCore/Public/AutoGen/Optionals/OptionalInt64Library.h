

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalInt64.h"

#include "OptionalInt64Library.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalInt64Library : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalInt64 MakeOptionalInt64(int64 Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Int64 To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalInt64 Conv_OptionalInt64FromValue(int64 Value);
};
