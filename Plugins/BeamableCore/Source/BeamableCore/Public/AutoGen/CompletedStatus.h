
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "CompletedStatus.generated.h"

UCLASS(BlueprintType)
class UCompletedStatus : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cycle")
	int32 Cycle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tier")
	int32 Tier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stage")
	int32 Stage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Delta")
	int32 Delta;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};