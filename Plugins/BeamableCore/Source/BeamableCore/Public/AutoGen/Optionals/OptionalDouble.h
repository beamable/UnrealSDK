
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"


#include "OptionalDouble.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalDoubleLibrary.MakeOptionalDouble"))
struct FOptionalDouble : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	double Val;

	FOptionalDouble();

	explicit FOptionalDouble(double Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};