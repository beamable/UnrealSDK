#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/Schedule.h"

#include "OptionalSchedule.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalScheduleLibrary.MakeOptional", BeamOptionalType="USchedule*"))
struct BEAMABLECORE_API FOptionalSchedule : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	USchedule* Val;

	FOptionalSchedule();

	explicit FOptionalSchedule(USchedule* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};