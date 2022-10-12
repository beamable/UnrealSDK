
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Enums/WebhookInvocationType.h"
#include "AutoGen/Enums/WebhookRetryType.h"

#include "WebhookInvocationStrategy.generated.h"

UCLASS(BlueprintType)
class UWebhookInvocationStrategy : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Invocation Type")
	EWebhookInvocationType InvocationType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Retry Type")
	EWebhookRetryType RetryType;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};