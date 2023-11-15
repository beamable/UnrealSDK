#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Enums/WebhookInvocationType.h"
#include "BeamableCore/Public/AutoGen/Enums/WebhookRetryType.h"

#include "WebhookInvocationStrategy.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UWebhookInvocationStrategy : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Invocation Type", Category="Beam")
	EWebhookInvocationType InvocationType = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Retry Type", Category="Beam")
	EWebhookRetryType RetryType = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};