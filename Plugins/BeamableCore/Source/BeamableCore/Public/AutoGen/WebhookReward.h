
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/WebhookInvocationStrategy.h"
#include "AutoGen/Optionals/OptionalWebhookComet.h"

#include "WebhookReward.generated.h"

UCLASS(BlueprintType)
class UWebhookReward : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Webhook Symbol")
	FOptionalString WebhookSymbol;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Strategy")
	UWebhookInvocationStrategy* Strategy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Web Hook Comet")
	FOptionalWebhookComet WebHookComet;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};