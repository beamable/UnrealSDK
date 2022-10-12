
#pragma once

#include "CoreMinimal.h"
#include "ChampionScore.h"

#include "ChampionScoreLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UChampionScoreLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ChampionScore To JSON String")
	static FString ChampionScoreToJsonString(const UChampionScore* Serializable, const bool Pretty);		
};