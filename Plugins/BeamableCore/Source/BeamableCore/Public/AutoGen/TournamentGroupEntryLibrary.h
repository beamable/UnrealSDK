#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/TournamentGroupEntry.h"

#include "TournamentGroupEntryLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTournamentGroupEntryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="TournamentGroupEntry To JSON String")
	static FString TournamentGroupEntryToJsonString(const UTournamentGroupEntry* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make TournamentGroupEntry", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UTournamentGroupEntry* Make(int64 Rank, double Score, int64 GroupId, int32 StageChange, TArray<UTournamentCurrencyReward*> CurrencyRewards, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break TournamentGroupEntry", meta=(NativeBreakFunc))
	static void Break(const UTournamentGroupEntry* Serializable, int64& Rank, double& Score, int64& GroupId, int32& StageChange, TArray<UTournamentCurrencyReward*>& CurrencyRewards);
};