#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/ChallengeSolution.h"

#include "OptionalChallengeSolution.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalChallengeSolutionLibrary.MakeOptional", BeamOptionalType="UChallengeSolution*"))
struct BEAMABLECORE_API FOptionalChallengeSolution : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UChallengeSolution* Val;

	FOptionalChallengeSolution();

	explicit FOptionalChallengeSolution(UChallengeSolution* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};