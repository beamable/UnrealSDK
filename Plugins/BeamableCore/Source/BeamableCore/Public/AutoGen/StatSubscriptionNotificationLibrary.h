#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/StatSubscriptionNotification.h"

#include "StatSubscriptionNotificationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UStatSubscriptionNotificationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - StatSubscriptionNotification To JSON String")
	static FString StatSubscriptionNotificationToJsonString(const UStatSubscriptionNotification* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make StatSubscriptionNotification", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UStatSubscriptionNotification* Make(TMap<FString, FString> StatsBefore, TMap<FString, FString> StatsAfter, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break StatSubscriptionNotification", meta=(NativeBreakFunc))
	static void Break(const UStatSubscriptionNotification* Serializable, TMap<FString, FString>& StatsBefore, TMap<FString, FString>& StatsAfter);
};