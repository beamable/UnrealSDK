#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamBackend/ReplacementTypes/BeamExternalIdentity.h"

#include "OptionalBeamExternalIdentity.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalBeamExternalIdentityLibrary.MakeOptional", BeamOptionalType="FBeamExternalIdentity"))
struct BEAMABLECORE_API FOptionalBeamExternalIdentity : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FBeamExternalIdentity Val;

	FOptionalBeamExternalIdentity();

	explicit FOptionalBeamExternalIdentity(FBeamExternalIdentity Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};