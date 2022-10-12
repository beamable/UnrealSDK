

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalSchedule.h"

#include "OptionalScheduleLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalScheduleLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalSchedule MakeOptionalSchedule(USchedule* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Schedule To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalSchedule Conv_OptionalScheduleFromValue(USchedule* Value);
};
