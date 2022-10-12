
#pragma once

#include "CoreMinimal.h"
#include "NotificationRequestData.h"

#include "NotificationRequestDataLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UNotificationRequestDataLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize NotificationRequestData To JSON String")
	static FString NotificationRequestDataToJsonString(const UNotificationRequestData* Serializable, const bool Pretty);		
};