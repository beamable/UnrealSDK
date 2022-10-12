
#pragma once

#include "CoreMinimal.h"
#include "EventPhaseRuntime.h"

#include "EventPhaseRuntimeLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEventPhaseRuntimeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EventPhaseRuntime To JSON String")
	static FString EventPhaseRuntimeToJsonString(const UEventPhaseRuntime* Serializable, const bool Pretty);		
};