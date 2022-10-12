
#pragma once

#include "CoreMinimal.h"
#include "MatchMakingRanking.h"

#include "MatchMakingRankingLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UMatchMakingRankingLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize MatchMakingRanking To JSON String")
	static FString MatchMakingRankingToJsonString(const UMatchMakingRanking* Serializable, const bool Pretty);		
};