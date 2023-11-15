#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamBackend/SemanticTypes/BeamContentManifestId.h"

#include "OptionalBeamContentManifestId.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalBeamContentManifestIdLibrary.MakeOptional", BeamOptionalType="FBeamContentManifestId"))
struct BEAMABLECORE_API FOptionalBeamContentManifestId : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FBeamContentManifestId Val;

	FOptionalBeamContentManifestId();

	explicit FOptionalBeamContentManifestId(FBeamContentManifestId Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};