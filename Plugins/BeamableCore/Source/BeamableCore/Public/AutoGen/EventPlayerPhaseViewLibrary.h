
#pragma once

#include "CoreMinimal.h"
#include "EventPlayerPhaseView.h"

#include "EventPlayerPhaseViewLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEventPlayerPhaseViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EventPlayerPhaseView To JSON String")
	static FString EventPlayerPhaseViewToJsonString(const UEventPlayerPhaseView* Serializable, const bool Pretty);		
};