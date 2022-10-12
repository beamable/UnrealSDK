
#pragma once

#include "CoreMinimal.h"
#include "StatSubscriptionNotification.h"

#include "StatSubscriptionNotificationLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UStatSubscriptionNotificationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize StatSubscriptionNotification To JSON String")
	static FString StatSubscriptionNotificationToJsonString(const UStatSubscriptionNotification* Serializable, const bool Pretty);		
};