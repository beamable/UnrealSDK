#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"


#include "OptionalMapOfDouble.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalMapOfDoubleLibrary.MakeOptional", BeamOptionalType="TMap<FString, double>"))
struct BEAMABLECORE_API FOptionalMapOfDouble : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TMap<FString, double> Val;

	FOptionalMapOfDouble();

	explicit FOptionalMapOfDouble(TMap<FString, double> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};