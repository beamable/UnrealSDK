#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/TournamentEntry.h"

#include "TournamentEntryLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTournamentEntryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - TournamentEntry To JSON String")
	static FString TournamentEntryToJsonString(const UTournamentEntry* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make TournamentEntry", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UTournamentEntry* Make(int64 Rank, double Score, int64 PlayerId, int32 StageChange, TArray<UTournamentCurrencyReward*> CurrencyRewards, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break TournamentEntry", meta=(NativeBreakFunc))
	static void Break(const UTournamentEntry* Serializable, int64& Rank, double& Score, int64& PlayerId, int32& StageChange, TArray<UTournamentCurrencyReward*>& CurrencyRewards);
};