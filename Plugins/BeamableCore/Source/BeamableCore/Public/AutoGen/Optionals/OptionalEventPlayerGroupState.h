#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/EventPlayerGroupState.h"

#include "OptionalEventPlayerGroupState.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalEventPlayerGroupStateLibrary.MakeOptional", BeamOptionalType="UEventPlayerGroupState*"))
struct BEAMABLECORE_API FOptionalEventPlayerGroupState : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UEventPlayerGroupState* Val;

	FOptionalEventPlayerGroupState();

	explicit FOptionalEventPlayerGroupState(UEventPlayerGroupState* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};