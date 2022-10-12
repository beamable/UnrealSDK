
#pragma once

#include "CoreMinimal.h"
#include "NotificationRequestBody.h"

#include "NotificationRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UNotificationRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize NotificationRequestBody To JSON String")
	static FString NotificationRequestBodyToJsonString(const UNotificationRequestBody* Serializable, const bool Pretty);		
};