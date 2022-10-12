
#pragma once

#include "CoreMinimal.h"
#include "WebhookReward.h"

#include "WebhookRewardLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UWebhookRewardLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize WebhookReward To JSON String")
	static FString WebhookRewardToJsonString(const UWebhookReward* Serializable, const bool Pretty);		
};