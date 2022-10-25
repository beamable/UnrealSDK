
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/StatsResponse.h"

#include "StatsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UStatsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - StatsResponse To JSON String")
	static FString StatsResponseToJsonString(const UStatsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make StatsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UStatsResponse* Make(int64 Id, TMap<FString, FString> Stats, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break StatsResponse", meta=(NativeBreakFunc))
	static void Break(const UStatsResponse* Serializable, int64& Id, TMap<FString, FString>& Stats);
};