
#pragma once

#include "CoreMinimal.h"
#include "AvailabilityRequestBody.h"

#include "AvailabilityRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAvailabilityRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AvailabilityRequestBody To JSON String")
	static FString AvailabilityRequestBodyToJsonString(const UAvailabilityRequestBody* Serializable, const bool Pretty);		
};