
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "AutoGen/ContentLimits.h"

#include "OptionalContentLimits.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalContentLimitsLibrary.MakeOptionalContentLimits"))
struct FOptionalContentLimits : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	UContentLimits* Val;

	FOptionalContentLimits();

	explicit FOptionalContentLimits(UContentLimits* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};