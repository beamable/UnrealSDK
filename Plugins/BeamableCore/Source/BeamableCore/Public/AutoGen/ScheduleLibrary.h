
#pragma once

#include "CoreMinimal.h"
#include "Schedule.h"

#include "ScheduleLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UScheduleLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize Schedule To JSON String")
	static FString ScheduleToJsonString(const USchedule* Serializable, const bool Pretty);		
};