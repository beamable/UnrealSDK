#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/ServicePlanActorBeamoLimits.h"

#include "OptionalServicePlanActorBeamoLimits.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalServicePlanActorBeamoLimitsLibrary.MakeOptional", BeamOptionalType="UServicePlanActorBeamoLimits*"))
struct BEAMABLECORE_API FOptionalServicePlanActorBeamoLimits : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UServicePlanActorBeamoLimits* Val;

	FOptionalServicePlanActorBeamoLimits();

	explicit FOptionalServicePlanActorBeamoLimits(UServicePlanActorBeamoLimits* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};