#pragma once
#include "BeamJsonSerializable.h"

#include "BeamArray.generated.h"


USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamArray : public FBeamJsonSerializable
{
	GENERATED_BODY()

	virtual void BeamSerialize(TUnrealJsonSerializer& Serializer) const override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;

	virtual void BeamDeserialize(const FString& JsonString) override;

	virtual void BeamDeserializeElements(const TArray<TSharedPtr<FJsonValue>>& Elements);
};
