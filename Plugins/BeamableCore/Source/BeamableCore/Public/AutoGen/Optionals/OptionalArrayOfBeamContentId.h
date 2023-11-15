#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"

#include "OptionalArrayOfBeamContentId.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfBeamContentIdLibrary.MakeOptional", BeamOptionalType="TArray<FBeamContentId>"))
struct BEAMABLECORE_API FOptionalArrayOfBeamContentId : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FBeamContentId> Val;

	FOptionalArrayOfBeamContentId();

	explicit FOptionalArrayOfBeamContentId(TArray<FBeamContentId> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};