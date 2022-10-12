
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/EventPlayerStateView.h"

#include "EventPlayerView.generated.h"

UCLASS(BlueprintType)
class UEventPlayerView : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Running")
	TArray<UEventPlayerStateView*> Running;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Done")
	TArray<UEventPlayerStateView*> Done;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};