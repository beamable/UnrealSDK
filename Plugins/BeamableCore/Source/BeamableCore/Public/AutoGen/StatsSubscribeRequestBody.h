
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "StatsSubscribeRequestBody.generated.h"

UCLASS(BlueprintType)
class UStatsSubscribeRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service")
	FString Service;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Subscriptions")
	TArray<FString> Subscriptions;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};