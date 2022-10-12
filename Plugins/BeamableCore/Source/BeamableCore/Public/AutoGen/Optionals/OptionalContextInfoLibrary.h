

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalContextInfo.h"

#include "OptionalContextInfoLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalContextInfoLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalContextInfo MakeOptionalContextInfo(UContextInfo* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ContextInfo To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalContextInfo Conv_OptionalContextInfoFromValue(UContextInfo* Value);
};
