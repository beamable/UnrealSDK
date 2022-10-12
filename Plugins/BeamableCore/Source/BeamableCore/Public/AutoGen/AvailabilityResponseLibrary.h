
#pragma once

#include "CoreMinimal.h"
#include "AvailabilityResponse.h"

#include "AvailabilityResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAvailabilityResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AvailabilityResponse To JSON String")
	static FString AvailabilityResponseToJsonString(const UAvailabilityResponse* Serializable, const bool Pretty);		
};