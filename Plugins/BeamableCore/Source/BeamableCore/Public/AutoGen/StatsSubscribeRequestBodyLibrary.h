#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/StatsSubscribeRequestBody.h"

#include "StatsSubscribeRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UStatsSubscribeRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="StatsSubscribeRequestBody To JSON String")
	static FString StatsSubscribeRequestBodyToJsonString(const UStatsSubscribeRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make StatsSubscribeRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UStatsSubscribeRequestBody* Make(FString Service, TArray<FString> Subscriptions, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break StatsSubscribeRequestBody", meta=(NativeBreakFunc))
	static void Break(const UStatsSubscribeRequestBody* Serializable, FString& Service, TArray<FString>& Subscriptions);
};