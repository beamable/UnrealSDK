#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RewardsResponse.h"

#include "RewardsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URewardsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Json", DisplayName="RewardsResponse To JSON String")
	static FString RewardsResponseToJsonString(const URewardsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make RewardsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URewardsResponse* Make(TArray<UTournamentCurrencyReward*> RewardCurrencies, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Break RewardsResponse", meta=(NativeBreakFunc))
	static void Break(const URewardsResponse* Serializable, TArray<UTournamentCurrencyReward*>& RewardCurrencies);
};