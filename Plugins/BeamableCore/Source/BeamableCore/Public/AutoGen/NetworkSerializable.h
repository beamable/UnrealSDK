
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "NetworkSerializable.generated.h"

UCLASS(BlueprintType)
class UNetworkSerializable : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};