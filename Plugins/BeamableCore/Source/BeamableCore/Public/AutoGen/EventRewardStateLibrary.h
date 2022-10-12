
#pragma once

#include "CoreMinimal.h"
#include "EventRewardState.h"

#include "EventRewardStateLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEventRewardStateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EventRewardState To JSON String")
	static FString EventRewardStateToJsonString(const UEventRewardState* Serializable, const bool Pretty);		
};