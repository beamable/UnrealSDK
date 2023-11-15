#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/ContentLimits.h"

#include "OptionalContentLimits.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalContentLimitsLibrary.MakeOptional", BeamOptionalType="UContentLimits*"))
struct BEAMABLECORE_API FOptionalContentLimits : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UContentLimits* Val;

	FOptionalContentLimits();

	explicit FOptionalContentLimits(UContentLimits* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};