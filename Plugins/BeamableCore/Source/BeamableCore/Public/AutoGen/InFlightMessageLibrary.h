
#pragma once

#include "CoreMinimal.h"
#include "InFlightMessage.h"

#include "InFlightMessageLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UInFlightMessageLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize InFlightMessage To JSON String")
	static FString InFlightMessageToJsonString(const UInFlightMessage* Serializable, const bool Pretty);		
};