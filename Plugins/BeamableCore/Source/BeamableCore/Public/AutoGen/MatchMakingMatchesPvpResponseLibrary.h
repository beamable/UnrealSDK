#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MatchMakingMatchesPvpResponse.h"

#include "MatchMakingMatchesPvpResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMatchMakingMatchesPvpResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - MatchMakingMatchesPvpResponse To JSON String")
	static FString MatchMakingMatchesPvpResponseToJsonString(const UMatchMakingMatchesPvpResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make MatchMakingMatchesPvpResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMatchMakingMatchesPvpResponse* Make(FString Result, int32 TotalEntries, UMatchMakingRanking* PlayerRank, TArray<UMatchMakingWindowResp*> Windows, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break MatchMakingMatchesPvpResponse", meta=(NativeBreakFunc))
	static void Break(const UMatchMakingMatchesPvpResponse* Serializable, FString& Result, int32& TotalEntries, UMatchMakingRanking*& PlayerRank, TArray<UMatchMakingWindowResp*>& Windows);
};