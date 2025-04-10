#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServiceRoute.h"

#include "ServiceRouteLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServiceRouteLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|4 - Json", DisplayName="ServiceRoute To JSON String")
	static FString ServiceRouteToJsonString(const UServiceRoute* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|3 - Backend", DisplayName="Make ServiceRoute", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UServiceRoute* Make(FString Service, FString Endpoint, EWebhookServiceType ServiceTypeStr, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|3 - Backend", DisplayName="Break ServiceRoute", meta=(NativeBreakFunc))
	static void Break(const UServiceRoute* Serializable, FString& Service, FString& Endpoint, EWebhookServiceType& ServiceTypeStr);
};