#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/ServicePlanActorServiceLimits.h"

#include "OptionalServicePlanActorServiceLimits.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalServicePlanActorServiceLimitsLibrary.MakeOptional", BeamOptionalType="UServicePlanActorServiceLimits*"))
struct BEAMABLECORE_API FOptionalServicePlanActorServiceLimits : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UServicePlanActorServiceLimits* Val;

	FOptionalServicePlanActorServiceLimits();

	explicit FOptionalServicePlanActorServiceLimits(UServicePlanActorServiceLimits* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};