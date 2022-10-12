

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfScheduleDefinition.h"

#include "OptionalArrayOfScheduleDefinitionLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfScheduleDefinitionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfScheduleDefinition MakeOptionalArrayOfScheduleDefinition(TArray<UScheduleDefinition*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UScheduleDefinition*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfScheduleDefinition Conv_OptionalArrayOfScheduleDefinitionFromValue(TArray<UScheduleDefinition*> Value);
};
