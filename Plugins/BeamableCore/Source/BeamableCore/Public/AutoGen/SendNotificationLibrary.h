
#pragma once

#include "CoreMinimal.h"
#include "SendNotification.h"

#include "SendNotificationLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API USendNotificationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize SendNotification To JSON String")
	static FString SendNotificationToJsonString(const USendNotification* Serializable, const bool Pretty);		
};