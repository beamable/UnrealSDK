#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamBackend/SemanticTypes/BeamCid.h"

#include "OptionalBeamCid.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalBeamCidLibrary.MakeOptional", BeamOptionalType="FBeamCid"))
struct BEAMABLECORE_API FOptionalBeamCid : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FBeamCid Val;

	FOptionalBeamCid();

	explicit FOptionalBeamCid(FBeamCid Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};