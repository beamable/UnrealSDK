
#pragma once

#include "CoreMinimal.h"
#include "EventPlayerStateView.h"

#include "EventPlayerStateViewLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEventPlayerStateViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EventPlayerStateView To JSON String")
	static FString EventPlayerStateViewToJsonString(const UEventPlayerStateView* Serializable, const bool Pretty);		
};