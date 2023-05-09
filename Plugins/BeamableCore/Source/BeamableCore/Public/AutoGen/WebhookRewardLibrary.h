#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/WebhookReward.h"

#include "WebhookRewardLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UWebhookRewardLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - WebhookReward To JSON String")
	static FString WebhookRewardToJsonString(const UWebhookReward* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make WebhookReward", meta=(DefaultToSelf="Outer", AdvancedDisplay="WebhookSymbol, WebHookComet, Outer", NativeMakeFunc))
	static UWebhookReward* Make(UWebhookInvocationStrategy* Strategy, FOptionalString WebhookSymbol, FOptionalWebhookComet WebHookComet, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break WebhookReward", meta=(NativeBreakFunc))
	static void Break(const UWebhookReward* Serializable, UWebhookInvocationStrategy*& Strategy, FOptionalString& WebhookSymbol, FOptionalWebhookComet& WebHookComet);
};