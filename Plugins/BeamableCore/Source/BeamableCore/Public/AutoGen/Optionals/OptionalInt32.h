#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "Serialization/BeamJsonUtils.h"

#include "OptionalInt32.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalInt32Library.MakeOptional", BeamOptionalType="int32"))
struct BEAMABLECORE_API FOptionalInt32 : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int32 Val;

	FOptionalInt32();

	explicit FOptionalInt32(int32 Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};