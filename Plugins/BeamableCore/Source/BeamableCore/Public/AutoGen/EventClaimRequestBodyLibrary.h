
#pragma once

#include "CoreMinimal.h"
#include "EventClaimRequestBody.h"

#include "EventClaimRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEventClaimRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EventClaimRequestBody To JSON String")
	static FString EventClaimRequestBodyToJsonString(const UEventClaimRequestBody* Serializable, const bool Pretty);		
};