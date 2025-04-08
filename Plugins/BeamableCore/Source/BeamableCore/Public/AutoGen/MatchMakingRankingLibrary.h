#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MatchMakingRanking.h"

#include "MatchMakingRankingLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMatchMakingRankingLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="MatchMakingRanking To JSON String")
	static FString MatchMakingRankingToJsonString(const UMatchMakingRanking* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make MatchMakingRanking", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMatchMakingRanking* Make(bool bIsUnranked, int64 Gt, int32 Rank, TMap<FString, FString> Variables, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break MatchMakingRanking", meta=(NativeBreakFunc))
	static void Break(const UMatchMakingRanking* Serializable, bool& bIsUnranked, int64& Gt, int32& Rank, TMap<FString, FString>& Variables);
};