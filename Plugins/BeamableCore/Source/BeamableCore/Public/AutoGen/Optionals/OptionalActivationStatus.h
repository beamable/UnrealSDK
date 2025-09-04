#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/Enums/BeamActivationStatus.h"

#include "OptionalActivationStatus.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalActivationStatusLibrary.MakeOptional", BeamOptionalType="EBeamActivationStatus"))
struct BEAMABLECORE_API FOptionalActivationStatus : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EBeamActivationStatus Val;

	FOptionalActivationStatus();

	explicit FOptionalActivationStatus(EBeamActivationStatus Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};