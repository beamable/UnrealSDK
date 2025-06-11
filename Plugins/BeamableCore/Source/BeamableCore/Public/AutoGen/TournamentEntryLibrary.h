#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/TournamentEntry.h"

#include "TournamentEntryLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTournamentEntryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Json", DisplayName="TournamentEntry To JSON String")
	static FString TournamentEntryToJsonString(const UTournamentEntry* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make TournamentEntry", meta=(DefaultToSelf="Outer", AdvancedDisplay="PreviousStageChange, NextStageChange, Outer", NativeMakeFunc))
	static UTournamentEntry* Make(int32 Stage, int32 Tier, int64 Rank, double Score, int64 PlayerId, int32 StageChange, TArray<UTournamentCurrencyReward*> CurrencyRewards, FOptionalInt32 PreviousStageChange, FOptionalInt32 NextStageChange, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Break TournamentEntry", meta=(NativeBreakFunc))
	static void Break(const UTournamentEntry* Serializable, int32& Stage, int32& Tier, int64& Rank, double& Score, int64& PlayerId, int32& StageChange, TArray<UTournamentCurrencyReward*>& CurrencyRewards, FOptionalInt32& PreviousStageChange, FOptionalInt32& NextStageChange);
};