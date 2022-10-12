
#pragma once

#include "CoreMinimal.h"
#include "Event.h"

#include "EventLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEventLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize Event To JSON String")
	static FString EventToJsonString(const UEvent* Serializable, const bool Pretty);		
};