#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"

#include "CompletedStatus.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UCompletedStatus : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cycle", Category="Beam")
	int32 Cycle = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tier", Category="Beam")
	int32 Tier = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stage", Category="Beam")
	int32 Stage = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Delta", Category="Beam")
	int32 Delta = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};