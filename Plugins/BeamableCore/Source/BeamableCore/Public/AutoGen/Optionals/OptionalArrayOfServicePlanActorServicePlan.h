#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/ServicePlanActorServicePlan.h"

#include "OptionalArrayOfServicePlanActorServicePlan.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfServicePlanActorServicePlanLibrary.MakeOptional", BeamOptionalType="TArray<UServicePlanActorServicePlan*>"))
struct BEAMABLECORE_API FOptionalArrayOfServicePlanActorServicePlan : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UServicePlanActorServicePlan*> Val;

	FOptionalArrayOfServicePlanActorServicePlan();

	explicit FOptionalArrayOfServicePlanActorServicePlan(TArray<UServicePlanActorServicePlan*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};