#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "Serialization/BeamJsonUtils.h"

#include "OptionalInt64.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalInt64Library.MakeOptional", BeamOptionalType="int64"))
struct BEAMABLECORE_API FOptionalInt64 : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int64 Val;

	FOptionalInt64();

	explicit FOptionalInt64(int64 Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};