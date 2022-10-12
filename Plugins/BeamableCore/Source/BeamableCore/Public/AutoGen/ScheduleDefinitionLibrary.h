
#pragma once

#include "CoreMinimal.h"
#include "ScheduleDefinition.h"

#include "ScheduleDefinitionLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UScheduleDefinitionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ScheduleDefinition To JSON String")
	static FString ScheduleDefinitionToJsonString(const UScheduleDefinition* Serializable, const bool Pretty);		
};