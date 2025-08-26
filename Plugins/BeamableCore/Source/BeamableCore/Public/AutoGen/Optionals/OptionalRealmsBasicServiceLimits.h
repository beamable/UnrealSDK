#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/RealmsBasicServiceLimits.h"

#include "OptionalRealmsBasicServiceLimits.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalRealmsBasicServiceLimitsLibrary.MakeOptional", BeamOptionalType="URealmsBasicServiceLimits*"))
struct BEAMABLECORE_API FOptionalRealmsBasicServiceLimits : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	URealmsBasicServiceLimits* Val;

	FOptionalRealmsBasicServiceLimits();

	explicit FOptionalRealmsBasicServiceLimits(URealmsBasicServiceLimits* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};