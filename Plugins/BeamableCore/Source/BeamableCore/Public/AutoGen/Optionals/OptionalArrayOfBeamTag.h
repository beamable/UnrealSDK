#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamBackend/ReplacementTypes/BeamTag.h"

#include "OptionalArrayOfBeamTag.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfBeamTagLibrary.MakeOptional", BeamOptionalType="TArray<FBeamTag>"))
struct BEAMABLECORE_API FOptionalArrayOfBeamTag : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FBeamTag> Val;

	FOptionalArrayOfBeamTag();

	explicit FOptionalArrayOfBeamTag(TArray<FBeamTag> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};