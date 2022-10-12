

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalMailRewards.h"

#include "OptionalMailRewardsLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalMailRewardsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalMailRewards MakeOptionalMailRewards(UMailRewards* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "MailRewards To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalMailRewards Conv_OptionalMailRewardsFromValue(UMailRewards* Value);
};
