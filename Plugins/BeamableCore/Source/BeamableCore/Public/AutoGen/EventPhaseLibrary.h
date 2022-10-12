
#pragma once

#include "CoreMinimal.h"
#include "EventPhase.h"

#include "EventPhaseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEventPhaseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EventPhase To JSON String")
	static FString EventPhaseToJsonString(const UEventPhase* Serializable, const bool Pretty);		
};