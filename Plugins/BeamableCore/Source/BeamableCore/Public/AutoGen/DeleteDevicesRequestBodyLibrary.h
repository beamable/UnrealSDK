
#pragma once

#include "CoreMinimal.h"
#include "DeleteDevicesRequestBody.h"

#include "DeleteDevicesRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteDevicesRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize DeleteDevicesRequestBody To JSON String")
	static FString DeleteDevicesRequestBodyToJsonString(const UDeleteDevicesRequestBody* Serializable, const bool Pretty);		
};