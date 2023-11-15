#pragma once
#include "BeamJsonSerializable.h"

#include "BeamMap.generated.h"


USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamMap : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	virtual void BeamSerialize(TUnrealJsonSerializer& Serializer) const override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;

	virtual void BeamDeserialize(const FString& JsonString) override;

	virtual void BeamDeserializeElements(const TSharedPtr<FJsonObject>& Bag);

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override final;
};