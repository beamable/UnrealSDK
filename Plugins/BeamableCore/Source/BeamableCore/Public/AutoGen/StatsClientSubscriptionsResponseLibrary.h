#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/StatsClientSubscriptionsResponse.h"

#include "StatsClientSubscriptionsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UStatsClientSubscriptionsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - StatsClientSubscriptionsResponse To JSON String")
	static FString StatsClientSubscriptionsResponseToJsonString(const UStatsClientSubscriptionsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make StatsClientSubscriptionsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UStatsClientSubscriptionsResponse* Make(TArray<UStatClientSubscriptionData*> Subscriptions, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break StatsClientSubscriptionsResponse", meta=(NativeBreakFunc))
	static void Break(const UStatsClientSubscriptionsResponse* Serializable, TArray<UStatClientSubscriptionData*>& Subscriptions);
};