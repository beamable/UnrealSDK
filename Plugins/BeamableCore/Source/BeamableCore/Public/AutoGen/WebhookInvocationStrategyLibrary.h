#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/WebhookInvocationStrategy.h"

#include "WebhookInvocationStrategyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UWebhookInvocationStrategyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - WebhookInvocationStrategy To JSON String")
	static FString WebhookInvocationStrategyToJsonString(const UWebhookInvocationStrategy* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make WebhookInvocationStrategy", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UWebhookInvocationStrategy* Make(EWebhookInvocationType InvocationType, EWebhookRetryType RetryType, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break WebhookInvocationStrategy", meta=(NativeBreakFunc))
	static void Break(const UWebhookInvocationStrategy* Serializable, EWebhookInvocationType& InvocationType, EWebhookRetryType& RetryType);
};