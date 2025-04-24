#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/WebhookReward.h"

#include "WebhookRewardLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UWebhookRewardLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Json", DisplayName="WebhookReward To JSON String")
	static FString WebhookRewardToJsonString(const UWebhookReward* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Make WebhookReward", meta=(DefaultToSelf="Outer", AdvancedDisplay="WebhookSymbol, WebHookComet, Outer", NativeMakeFunc))
	static UWebhookReward* Make(UWebhookInvocationStrategy* Strategy, FOptionalString WebhookSymbol, FOptionalWebhookComet WebHookComet, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Break WebhookReward", meta=(NativeBreakFunc))
	static void Break(const UWebhookReward* Serializable, UWebhookInvocationStrategy*& Strategy, FOptionalString& WebhookSymbol, FOptionalWebhookComet& WebHookComet);
};