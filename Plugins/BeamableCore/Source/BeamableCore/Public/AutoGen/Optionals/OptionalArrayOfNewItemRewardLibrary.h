

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfNewItemReward.h"

#include "OptionalArrayOfNewItemRewardLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfNewItemRewardLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfNewItemReward MakeOptionalArrayOfNewItemReward(TArray<UNewItemReward*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UNewItemReward*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfNewItemReward Conv_OptionalArrayOfNewItemRewardFromValue(TArray<UNewItemReward*> Value);
};
