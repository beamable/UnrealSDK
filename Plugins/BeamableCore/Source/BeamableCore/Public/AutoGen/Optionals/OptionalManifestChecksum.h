
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "AutoGen/ManifestChecksum.h"

#include "OptionalManifestChecksum.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalManifestChecksumLibrary.MakeOptional", BeamOptionalType="UManifestChecksum*"))
struct BEAMABLECORE_API FOptionalManifestChecksum : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	UManifestChecksum* Val;

	FOptionalManifestChecksum();

	explicit FOptionalManifestChecksum(UManifestChecksum* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};