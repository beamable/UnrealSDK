#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Enums/BeamWebhookInvocationType.h"
#include "BeamableCore/Public/AutoGen/Enums/BeamWebhookRetryType.h"

#include "WebhookInvocationStrategy.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UWebhookInvocationStrategy : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Invocation Type", Category="Beam")
	EBeamWebhookInvocationType InvocationType = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Retry Type", Category="Beam")
	EBeamWebhookRetryType RetryType = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};