
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "VipBonus.generated.h"

UCLASS(BlueprintType)
class UVipBonus : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Currency")
	FString Currency;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Multiplier")
	double Multiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Round To Nearest")
	int32 RoundToNearest;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};