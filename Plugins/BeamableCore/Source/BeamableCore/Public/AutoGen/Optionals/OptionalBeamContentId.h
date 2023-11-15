#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"

#include "OptionalBeamContentId.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalBeamContentIdLibrary.MakeOptional", BeamOptionalType="FBeamContentId"))
struct BEAMABLECORE_API FOptionalBeamContentId : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FBeamContentId Val;

	FOptionalBeamContentId();

	explicit FOptionalBeamContentId(FBeamContentId Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};