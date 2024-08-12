#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/SupportedFederation.h"

#include "OptionalSupportedFederation.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalSupportedFederationLibrary.MakeOptional", BeamOptionalType="USupportedFederation*"))
struct BEAMABLECORE_API FOptionalSupportedFederation : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	USupportedFederation* Val;

	FOptionalSupportedFederation();

	explicit FOptionalSupportedFederation(USupportedFederation* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};