#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamBackend/SemanticTypes/BeamPid.h"

#include "OptionalBeamPid.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalBeamPidLibrary.MakeOptional", BeamOptionalType="FBeamPid"))
struct BEAMABLECORE_API FOptionalBeamPid : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FBeamPid Val;

	FOptionalBeamPid();

	explicit FOptionalBeamPid(FBeamPid Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};