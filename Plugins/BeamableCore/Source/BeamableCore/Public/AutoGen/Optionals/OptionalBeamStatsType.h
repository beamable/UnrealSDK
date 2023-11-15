#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamBackend/SemanticTypes/BeamStatsType.h"

#include "OptionalBeamStatsType.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalBeamStatsTypeLibrary.MakeOptional", BeamOptionalType="FBeamStatsType"))
struct BEAMABLECORE_API FOptionalBeamStatsType : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FBeamStatsType Val;

	FOptionalBeamStatsType();

	explicit FOptionalBeamStatsType(FBeamStatsType Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};