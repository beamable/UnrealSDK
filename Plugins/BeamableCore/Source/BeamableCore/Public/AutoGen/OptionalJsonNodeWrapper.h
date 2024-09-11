#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"

#include "OptionalJsonNodeWrapper.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UOptionalJsonNodeWrapper : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Node", Category="Beam")
	FOptionalString Node = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};