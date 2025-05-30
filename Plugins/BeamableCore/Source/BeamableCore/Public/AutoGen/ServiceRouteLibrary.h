#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServiceRoute.h"

#include "ServiceRouteLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServiceRouteLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Json", DisplayName="ServiceRoute To JSON String")
	static FString ServiceRouteToJsonString(const UServiceRoute* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Make ServiceRoute", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UServiceRoute* Make(FString Service, FString Endpoint, EBeamWebhookServiceType ServiceTypeStr, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Break ServiceRoute", meta=(NativeBreakFunc))
	static void Break(const UServiceRoute* Serializable, FString& Service, FString& Endpoint, EBeamWebhookServiceType& ServiceTypeStr);
};