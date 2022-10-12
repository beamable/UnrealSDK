
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalMapOfString.h"

#include "EventInventoryRewardItem.generated.h"

UCLASS(BlueprintType)
class UEventInventoryRewardItem : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Properties")
	FOptionalMapOfString Properties;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};