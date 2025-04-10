#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SendNotification.h"

#include "SendNotificationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USendNotificationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Push|Utils|Json", DisplayName="SendNotification To JSON String")
	static FString SendNotificationToJsonString(const USendNotification* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Push|Utils|Make/Break", DisplayName="Make SendNotification", meta=(DefaultToSelf="Outer", AdvancedDisplay="Title, Body, Outer", NativeMakeFunc))
	static USendNotification* Make(FOptionalString Title, FOptionalString Body, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Push|Utils|Make/Break", DisplayName="Break SendNotification", meta=(NativeBreakFunc))
	static void Break(const USendNotification* Serializable, FOptionalString& Title, FOptionalString& Body);
};