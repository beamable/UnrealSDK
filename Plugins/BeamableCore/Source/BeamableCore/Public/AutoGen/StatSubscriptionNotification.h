
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "StatSubscriptionNotification.generated.h"

UCLASS(BlueprintType)
class UStatSubscriptionNotification : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stats Before")
	TMap<FString, FString> StatsBefore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stats After")
	TMap<FString, FString> StatsAfter;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};