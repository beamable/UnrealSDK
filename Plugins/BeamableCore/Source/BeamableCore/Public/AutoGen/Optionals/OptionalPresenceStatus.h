#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/Enums/BeamPresenceStatus.h"

#include "OptionalPresenceStatus.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalPresenceStatusLibrary.MakeOptional", BeamOptionalType="EBeamPresenceStatus"))
struct BEAMABLECORE_API FOptionalPresenceStatus : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EBeamPresenceStatus Val;

	FOptionalPresenceStatus();

	explicit FOptionalPresenceStatus(EBeamPresenceStatus Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};