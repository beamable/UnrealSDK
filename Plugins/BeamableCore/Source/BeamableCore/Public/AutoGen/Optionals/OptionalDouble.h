#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "Serialization/BeamJsonUtils.h"

#include "OptionalDouble.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalDoubleLibrary.MakeOptional", BeamOptionalType="double"))
struct BEAMABLECORE_API FOptionalDouble : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	double Val;

	FOptionalDouble();

	explicit FOptionalDouble(double Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};