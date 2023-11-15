#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/EventPhaseTime.h"

#include "OptionalArrayOfEventPhaseTime.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfEventPhaseTimeLibrary.MakeOptional", BeamOptionalType="TArray<UEventPhaseTime*>"))
struct BEAMABLECORE_API FOptionalArrayOfEventPhaseTime : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UEventPhaseTime*> Val;

	FOptionalArrayOfEventPhaseTime();

	explicit FOptionalArrayOfEventPhaseTime(TArray<UEventPhaseTime*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};