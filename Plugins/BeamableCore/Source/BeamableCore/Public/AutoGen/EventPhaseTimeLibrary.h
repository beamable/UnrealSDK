
#pragma once

#include "CoreMinimal.h"
#include "EventPhaseTime.h"

#include "EventPhaseTimeLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEventPhaseTimeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EventPhaseTime To JSON String")
	static FString EventPhaseTimeToJsonString(const UEventPhaseTime* Serializable, const bool Pretty);		
};