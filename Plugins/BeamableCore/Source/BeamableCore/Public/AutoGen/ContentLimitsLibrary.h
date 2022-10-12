
#pragma once

#include "CoreMinimal.h"
#include "ContentLimits.h"

#include "ContentLimitsLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UContentLimitsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ContentLimits To JSON String")
	static FString ContentLimitsToJsonString(const UContentLimits* Serializable, const bool Pretty);		
};