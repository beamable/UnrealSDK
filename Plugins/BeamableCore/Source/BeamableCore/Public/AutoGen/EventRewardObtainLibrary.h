
#pragma once

#include "CoreMinimal.h"
#include "EventRewardObtain.h"

#include "EventRewardObtainLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEventRewardObtainLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EventRewardObtain To JSON String")
	static FString EventRewardObtainToJsonString(const UEventRewardObtain* Serializable, const bool Pretty);		
};