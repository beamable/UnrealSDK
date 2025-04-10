#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/StatsResponse.h"

#include "StatsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UStatsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|4 - Json", DisplayName="StatsResponse To JSON String")
	static FString StatsResponseToJsonString(const UStatsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|3 - Backend", DisplayName="Make StatsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UStatsResponse* Make(FBeamGamerTag Id, TMap<FString, FString> Stats, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|3 - Backend", DisplayName="Break StatsResponse", meta=(NativeBreakFunc))
	static void Break(const UStatsResponse* Serializable, FBeamGamerTag& Id, TMap<FString, FString>& Stats);
};