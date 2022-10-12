

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalPlayerReward.h"

#include "OptionalPlayerRewardLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalPlayerRewardLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalPlayerReward MakeOptionalPlayerReward(UPlayerReward* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "PlayerReward To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalPlayerReward Conv_OptionalPlayerRewardFromValue(UPlayerReward* Value);
};
