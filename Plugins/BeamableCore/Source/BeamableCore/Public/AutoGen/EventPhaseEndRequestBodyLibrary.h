
#pragma once

#include "CoreMinimal.h"
#include "EventPhaseEndRequestBody.h"

#include "EventPhaseEndRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEventPhaseEndRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EventPhaseEndRequestBody To JSON String")
	static FString EventPhaseEndRequestBodyToJsonString(const UEventPhaseEndRequestBody* Serializable, const bool Pretty);		
};