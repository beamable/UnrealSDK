#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MatchMakingWindowResp.h"

#include "MatchMakingWindowRespLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMatchMakingWindowRespLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - MatchMakingWindowResp To JSON String")
	static FString MatchMakingWindowRespToJsonString(const UMatchMakingWindowResp* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make MatchMakingWindowResp", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMatchMakingWindowResp* Make(int32 Difficulty, TArray<UMatchMakingRanking*> Matches, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break MatchMakingWindowResp", meta=(NativeBreakFunc))
	static void Break(const UMatchMakingWindowResp* Serializable, int32& Difficulty, TArray<UMatchMakingRanking*>& Matches);
};