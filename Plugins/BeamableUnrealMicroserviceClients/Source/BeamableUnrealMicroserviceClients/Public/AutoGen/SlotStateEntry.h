#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"

#include "SlotStateEntry.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLEUNREALMICROSERVICECLIENTS_API USlotStateEntry : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Slot Id", Category="Beam")
	FString SlotId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Seed Id", Category="Beam")
	FString SeedId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Harvest Id", Category="Beam")
	FString HarvestId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Planted At", Category="Beam")
	int64 PlantedAt = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Grow Secs", Category="Beam")
	int32 GrowSecs = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};