
#pragma once

#include "CoreMinimal.h"
#include "TournamentCurrencyReward.h"

#include "TournamentCurrencyRewardLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UTournamentCurrencyRewardLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize TournamentCurrencyReward To JSON String")
	static FString TournamentCurrencyRewardToJsonString(const UTournamentCurrencyReward* Serializable, const bool Pretty);		
};