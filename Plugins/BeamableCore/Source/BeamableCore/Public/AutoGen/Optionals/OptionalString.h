#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "Serialization/BeamJsonUtils.h"

#include "OptionalString.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalStringLibrary.MakeOptional", BeamOptionalType="FString"))
struct BEAMABLECORE_API FOptionalString : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString Val;

	FOptionalString();

	explicit FOptionalString(FString Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};