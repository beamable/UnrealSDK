#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/EventPhaseRuntime.h"

#include "OptionalEventPhaseRuntime.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalEventPhaseRuntimeLibrary.MakeOptional", BeamOptionalType="UEventPhaseRuntime*"))
struct BEAMABLECORE_API FOptionalEventPhaseRuntime : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	UEventPhaseRuntime* Val;

	FOptionalEventPhaseRuntime();

	explicit FOptionalEventPhaseRuntime(UEventPhaseRuntime* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};