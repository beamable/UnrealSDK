
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/EventPlayerStateView.h"

#include "EventClaimResponse.generated.h"

UCLASS(BlueprintType)
class UEventClaimResponse : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="View")
	UEventPlayerStateView* View;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Game Rsp Json")
	FString GameRspJson;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};