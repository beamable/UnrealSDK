#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "Serialization/BeamJsonUtils.h"

#include "OptionalBool.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalBoolLibrary.MakeOptional", BeamOptionalType="bool"))
struct BEAMABLECORE_API FOptionalBool : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool Val;

	FOptionalBool();

	explicit FOptionalBool(bool Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};