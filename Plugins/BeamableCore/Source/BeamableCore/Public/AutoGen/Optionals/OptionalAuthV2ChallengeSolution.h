#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/AuthV2ChallengeSolution.h"

#include "OptionalAuthV2ChallengeSolution.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalAuthV2ChallengeSolutionLibrary.MakeOptional", BeamOptionalType="UAuthV2ChallengeSolution*"))
struct BEAMABLECORE_API FOptionalAuthV2ChallengeSolution : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UAuthV2ChallengeSolution* Val;

	FOptionalAuthV2ChallengeSolution();

	explicit FOptionalAuthV2ChallengeSolution(UAuthV2ChallengeSolution* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};