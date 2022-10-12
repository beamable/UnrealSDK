
#pragma once

#include "CoreMinimal.h"
#include "EventPlayerGroupState.h"

#include "EventPlayerGroupStateLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEventPlayerGroupStateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EventPlayerGroupState To JSON String")
	static FString EventPlayerGroupStateToJsonString(const UEventPlayerGroupState* Serializable, const bool Pretty);		
};