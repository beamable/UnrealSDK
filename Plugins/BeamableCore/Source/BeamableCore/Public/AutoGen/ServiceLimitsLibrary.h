
#pragma once

#include "CoreMinimal.h"
#include "ServiceLimits.h"

#include "ServiceLimitsLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UServiceLimitsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ServiceLimits To JSON String")
	static FString ServiceLimitsToJsonString(const UServiceLimits* Serializable, const bool Pretty);		
};