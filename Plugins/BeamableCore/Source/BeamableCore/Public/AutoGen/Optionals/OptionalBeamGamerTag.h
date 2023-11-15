#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamBackend/SemanticTypes/BeamGamerTag.h"

#include "OptionalBeamGamerTag.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalBeamGamerTagLibrary.MakeOptional", BeamOptionalType="FBeamGamerTag"))
struct BEAMABLECORE_API FOptionalBeamGamerTag : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FBeamGamerTag Val;

	FOptionalBeamGamerTag();

	explicit FOptionalBeamGamerTag(FBeamGamerTag Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};