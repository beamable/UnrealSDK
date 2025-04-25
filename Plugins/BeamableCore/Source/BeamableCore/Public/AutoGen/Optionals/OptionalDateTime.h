#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "Serialization/BeamJsonUtils.h"

#include "OptionalDateTime.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalDateTimeLibrary.MakeOptional", BeamOptionalType="FDateTime"))
struct BEAMABLECORE_API FOptionalDateTime : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FDateTime Val;

	FOptionalDateTime();

	explicit FOptionalDateTime(FDateTime Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};