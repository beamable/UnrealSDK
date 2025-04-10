#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/StatsUnsubscribeRequestBody.h"

#include "StatsUnsubscribeRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UStatsUnsubscribeRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Json", DisplayName="StatsUnsubscribeRequestBody To JSON String")
	static FString StatsUnsubscribeRequestBodyToJsonString(const UStatsUnsubscribeRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Make/Break", DisplayName="Make StatsUnsubscribeRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Subscriptions, Outer", NativeMakeFunc))
	static UStatsUnsubscribeRequestBody* Make(FString Service, FOptionalArrayOfString Subscriptions, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Make/Break", DisplayName="Break StatsUnsubscribeRequestBody", meta=(NativeBreakFunc))
	static void Break(const UStatsUnsubscribeRequestBody* Serializable, FString& Service, FOptionalArrayOfString& Subscriptions);
};