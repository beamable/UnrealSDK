
#pragma once

#include "CoreMinimal.h"
#include "EventRewardContent.h"

#include "EventRewardContentLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEventRewardContentLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EventRewardContent To JSON String")
	static FString EventRewardContentToJsonString(const UEventRewardContent* Serializable, const bool Pretty);		
};