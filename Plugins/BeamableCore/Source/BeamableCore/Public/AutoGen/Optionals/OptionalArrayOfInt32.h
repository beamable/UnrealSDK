#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"


#include "OptionalArrayOfInt32.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfInt32Library.MakeOptional", BeamOptionalType="TArray<int32>"))
struct BEAMABLECORE_API FOptionalArrayOfInt32 : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<int32> Val;

	FOptionalArrayOfInt32();

	explicit FOptionalArrayOfInt32(TArray<int32> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};