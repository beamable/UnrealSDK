
#pragma once

#include "CoreMinimal.h"
#include "WebhookInvocationStrategy.h"

#include "WebhookInvocationStrategyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UWebhookInvocationStrategyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize WebhookInvocationStrategy To JSON String")
	static FString WebhookInvocationStrategyToJsonString(const UWebhookInvocationStrategy* Serializable, const bool Pretty);		
};