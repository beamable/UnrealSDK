
#pragma once

#include "CoreMinimal.h"
#include "EventPlayerView.h"

#include "EventPlayerViewLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEventPlayerViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EventPlayerView To JSON String")
	static FString EventPlayerViewToJsonString(const UEventPlayerView* Serializable, const bool Pretty);		
};