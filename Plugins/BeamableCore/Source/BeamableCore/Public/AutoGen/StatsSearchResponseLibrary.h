#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/StatsSearchResponse.h"

#include "StatsSearchResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UStatsSearchResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Stats|4 - Json", DisplayName="StatsSearchResponse To JSON String")
	static FString StatsSearchResponseToJsonString(const UStatsSearchResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Stats|3 - Backend", DisplayName="Make StatsSearchResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UStatsSearchResponse* Make(TArray<FBeamGamerTag> Ids, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Stats|3 - Backend", DisplayName="Break StatsSearchResponse", meta=(NativeBreakFunc))
	static void Break(const UStatsSearchResponse* Serializable, TArray<FBeamGamerTag>& Ids);
};