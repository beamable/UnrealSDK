#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Enums/BeamWebhookServiceType.h"

#include "ServiceRoute.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UServiceRoute : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service", Category="Beam")
	FString Service = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Endpoint", Category="Beam")
	FString Endpoint = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Type Str", Category="Beam")
	EBeamWebhookServiceType ServiceTypeStr = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};