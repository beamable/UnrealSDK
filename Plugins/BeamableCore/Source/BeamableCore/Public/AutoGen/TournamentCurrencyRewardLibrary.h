#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/TournamentCurrencyReward.h"

#include "TournamentCurrencyRewardLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTournamentCurrencyRewardLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - TournamentCurrencyReward To JSON String")
	static FString TournamentCurrencyRewardToJsonString(const UTournamentCurrencyReward* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make TournamentCurrencyReward", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UTournamentCurrencyReward* Make(FString Symbol, int64 Amount, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break TournamentCurrencyReward", meta=(NativeBreakFunc))
	static void Break(const UTournamentCurrencyReward* Serializable, FString& Symbol, int64& Amount);
};