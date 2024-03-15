#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamBackend/SemanticTypes/BeamGamerTag.h"

#include "OptionalArrayOfBeamGamerTag.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfBeamGamerTagLibrary.MakeOptional", BeamOptionalType="TArray<FBeamGamerTag>"))
struct BEAMABLECORE_API FOptionalArrayOfBeamGamerTag : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FBeamGamerTag> Val;

	FOptionalArrayOfBeamGamerTag();

	explicit FOptionalArrayOfBeamGamerTag(TArray<FBeamGamerTag> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};