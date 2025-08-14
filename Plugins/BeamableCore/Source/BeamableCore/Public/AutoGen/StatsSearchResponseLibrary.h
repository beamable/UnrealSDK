#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/StatsSearchResponse.h"

#include "StatsSearchResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UStatsSearchResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Json", DisplayName="StatsSearchResponse To JSON String")
	static FString StatsSearchResponseToJsonString(const UStatsSearchResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Make/Break", DisplayName="Make StatsSearchResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Total, Outer", NativeMakeFunc))
	static UStatsSearchResponse* Make(int32 Offset, int32 Limit, TArray<FBeamGamerTag> Ids, FOptionalInt64 Total, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Make/Break", DisplayName="Break StatsSearchResponse", meta=(NativeBreakFunc))
	static void Break(const UStatsSearchResponse* Serializable, int32& Offset, int32& Limit, TArray<FBeamGamerTag>& Ids, FOptionalInt64& Total);
};