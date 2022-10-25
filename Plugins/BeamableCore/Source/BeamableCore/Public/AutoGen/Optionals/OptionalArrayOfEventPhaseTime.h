
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "AutoGen/EventPhaseTime.h"

#include "OptionalArrayOfEventPhaseTime.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalArrayOfEventPhaseTimeLibrary.MakeOptional"))
struct BEAMABLECORE_API FOptionalArrayOfEventPhaseTime : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<UEventPhaseTime*> Val;

	FOptionalArrayOfEventPhaseTime();

	explicit FOptionalArrayOfEventPhaseTime(TArray<UEventPhaseTime*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};