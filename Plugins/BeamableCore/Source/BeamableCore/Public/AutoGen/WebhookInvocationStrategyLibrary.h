#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/WebhookInvocationStrategy.h"

#include "WebhookInvocationStrategyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UWebhookInvocationStrategyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Json", DisplayName="WebhookInvocationStrategy To JSON String")
	static FString WebhookInvocationStrategyToJsonString(const UWebhookInvocationStrategy* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Make WebhookInvocationStrategy", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UWebhookInvocationStrategy* Make(EBeamWebhookInvocationType InvocationType, EBeamWebhookRetryType RetryType, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Break WebhookInvocationStrategy", meta=(NativeBreakFunc))
	static void Break(const UWebhookInvocationStrategy* Serializable, EBeamWebhookInvocationType& InvocationType, EBeamWebhookRetryType& RetryType);
};