#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/Enums/BeamFederationType.h"

#include "OptionalFederationType.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalFederationTypeLibrary.MakeOptional", BeamOptionalType="EBeamFederationType"))
struct BEAMABLECORE_API FOptionalFederationType : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EBeamFederationType Val;

	FOptionalFederationType();

	explicit FOptionalFederationType(EBeamFederationType Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};