#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/EventPlayerPhaseView.h"

#include "OptionalEventPlayerPhaseView.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalEventPlayerPhaseViewLibrary.MakeOptional", BeamOptionalType="UEventPlayerPhaseView*"))
struct BEAMABLECORE_API FOptionalEventPlayerPhaseView : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UEventPlayerPhaseView* Val;

	FOptionalEventPlayerPhaseView();

	explicit FOptionalEventPlayerPhaseView(UEventPlayerPhaseView* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};