#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamBackend/ReplacementTypes/BeamExternalIdentity.h"

#include "OptionalArrayOfBeamExternalIdentity.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfBeamExternalIdentityLibrary.MakeOptional", BeamOptionalType="TArray<FBeamExternalIdentity>"))
struct BEAMABLECORE_API FOptionalArrayOfBeamExternalIdentity : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FBeamExternalIdentity> Val;

	FOptionalArrayOfBeamExternalIdentity();

	explicit FOptionalArrayOfBeamExternalIdentity(TArray<FBeamExternalIdentity> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};