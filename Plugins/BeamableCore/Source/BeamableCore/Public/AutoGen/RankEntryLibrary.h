#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/RankEntry.h"

#include "RankEntryLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URankEntryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - RankEntry To JSON String")
	static FString RankEntryToJsonString(const URankEntry* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make RankEntry", meta=(DefaultToSelf="Outer", AdvancedDisplay="Score, Stats, Outer", NativeMakeFunc))
	static URankEntry* Make(int64 Rank, int64 Gt, TMap<FString, int64> Columns, FOptionalDouble Score, FOptionalArrayOfRankEntryStat Stats, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break RankEntry", meta=(NativeBreakFunc))
	static void Break(const URankEntry* Serializable, int64& Rank, int64& Gt, TMap<FString, int64>& Columns, FOptionalDouble& Score, FOptionalArrayOfRankEntryStat& Stats);
};