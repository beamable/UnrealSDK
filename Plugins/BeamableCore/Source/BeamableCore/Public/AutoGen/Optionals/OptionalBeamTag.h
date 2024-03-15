#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamBackend/ReplacementTypes/BeamTag.h"

#include "OptionalBeamTag.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalBeamTagLibrary.MakeOptional", BeamOptionalType="FBeamTag"))
struct BEAMABLECORE_API FOptionalBeamTag : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FBeamTag Val;

	FOptionalBeamTag();

	explicit FOptionalBeamTag(FBeamTag Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};