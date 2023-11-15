#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/ServiceLimits.h"

#include "OptionalServiceLimits.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalServiceLimitsLibrary.MakeOptional", BeamOptionalType="UServiceLimits*"))
struct BEAMABLECORE_API FOptionalServiceLimits : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UServiceLimits* Val;

	FOptionalServiceLimits();

	explicit FOptionalServiceLimits(UServiceLimits* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};