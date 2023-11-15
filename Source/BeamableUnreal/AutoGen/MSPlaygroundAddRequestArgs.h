#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"


#include "MSPlaygroundAddRequestArgs.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREAL_API UMSPlaygroundAddRequestArgs : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="A", Category="Beam")
	int32 A = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B", Category="Beam")
	int32 B = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};