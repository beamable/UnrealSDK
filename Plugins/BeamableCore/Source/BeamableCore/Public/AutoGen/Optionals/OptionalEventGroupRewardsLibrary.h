

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalEventGroupRewards.h"

#include "OptionalEventGroupRewardsLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalEventGroupRewardsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalEventGroupRewards MakeOptionalEventGroupRewards(UEventGroupRewards* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "EventGroupRewards To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalEventGroupRewards Conv_OptionalEventGroupRewardsFromValue(UEventGroupRewards* Value);
};
