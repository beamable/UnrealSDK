
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/EventPlayerStateView.h"

#include "EventPlayerView.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventPlayerView : public UObject, public FBeamJsonSerializable, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Running", Category="Beam")
	TArray<UEventPlayerStateView*> Running;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Done", Category="Beam")
	TArray<UEventPlayerStateView*> Done;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};