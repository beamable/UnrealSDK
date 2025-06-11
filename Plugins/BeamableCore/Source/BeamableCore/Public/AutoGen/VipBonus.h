#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"

#include "VipBonus.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UVipBonus : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Currency", Category="Beam")
	FString Currency = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Multiplier", Category="Beam")
	double Multiplier = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Round To Nearest", Category="Beam")
	int32 RoundToNearest = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};