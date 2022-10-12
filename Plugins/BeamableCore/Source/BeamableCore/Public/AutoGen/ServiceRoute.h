
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Enums/WebhookServiceType.h"

#include "ServiceRoute.generated.h"

UCLASS(BlueprintType)
class UServiceRoute : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service")
	FString Service;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Endpoint")
	FString Endpoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Type Str")
	EWebhookServiceType ServiceTypeStr;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};