
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/StatsSearchResponse.h"

#include "StatsSearchResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UStatsSearchResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - StatsSearchResponse To JSON String")
	static FString StatsSearchResponseToJsonString(const UStatsSearchResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make StatsSearchResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UStatsSearchResponse* Make(TArray<int64> Ids, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break StatsSearchResponse", meta=(NativeBreakFunc))
	static void Break(const UStatsSearchResponse* Serializable, TArray<int64>& Ids);
};