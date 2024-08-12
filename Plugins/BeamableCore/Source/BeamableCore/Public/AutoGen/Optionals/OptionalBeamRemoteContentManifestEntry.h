#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamBackend/ReplacementTypes/BeamRemoteContentManifestEntry.h"

#include "OptionalBeamRemoteContentManifestEntry.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalBeamRemoteContentManifestEntryLibrary.MakeOptional", BeamOptionalType="FBeamRemoteContentManifestEntry"))
struct BEAMABLECORE_API FOptionalBeamRemoteContentManifestEntry : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FBeamRemoteContentManifestEntry Val;

	FOptionalBeamRemoteContentManifestEntry();

	explicit FOptionalBeamRemoteContentManifestEntry(FBeamRemoteContentManifestEntry Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};