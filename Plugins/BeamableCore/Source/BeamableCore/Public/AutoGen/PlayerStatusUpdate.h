
#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalInt32.h"
#include "AutoGen/Optionals/OptionalDouble.h"

#include "PlayerStatusUpdate.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPlayerStatusUpdate : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tier", Category="Beam")
	FOptionalInt32 Tier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stage", Category="Beam")
	FOptionalInt32 Stage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score", Category="Beam")
	FOptionalDouble Score;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};