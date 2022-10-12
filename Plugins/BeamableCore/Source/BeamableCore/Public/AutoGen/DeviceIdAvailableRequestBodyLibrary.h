
#pragma once

#include "CoreMinimal.h"
#include "DeviceIdAvailableRequestBody.h"

#include "DeviceIdAvailableRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UDeviceIdAvailableRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize DeviceIdAvailableRequestBody To JSON String")
	static FString DeviceIdAvailableRequestBodyToJsonString(const UDeviceIdAvailableRequestBody* Serializable, const bool Pretty);		
};