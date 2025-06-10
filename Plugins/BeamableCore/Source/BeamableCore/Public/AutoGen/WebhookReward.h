#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/WebhookInvocationStrategy.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalWebhookComet.h"

#include "WebhookReward.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UWebhookReward : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Strategy", Category="Beam")
	UWebhookInvocationStrategy* Strategy = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Webhook Symbol", Category="Beam")
	FOptionalString WebhookSymbol = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Web Hook Comet", Category="Beam")
	FOptionalWebhookComet WebHookComet = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};