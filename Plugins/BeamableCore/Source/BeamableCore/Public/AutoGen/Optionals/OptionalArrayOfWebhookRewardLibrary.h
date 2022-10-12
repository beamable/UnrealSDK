

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfWebhookReward.h"

#include "OptionalArrayOfWebhookRewardLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfWebhookRewardLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfWebhookReward MakeOptionalArrayOfWebhookReward(TArray<UWebhookReward*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UWebhookReward*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfWebhookReward Conv_OptionalArrayOfWebhookRewardFromValue(TArray<UWebhookReward*> Value);
};
