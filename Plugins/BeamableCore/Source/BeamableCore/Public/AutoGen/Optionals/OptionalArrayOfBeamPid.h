
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamBackend/SemanticTypes/BeamPid.h"

#include "OptionalArrayOfBeamPid.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalArrayOfBeamPidLibrary.MakeOptional", BeamOptionalType="TArray<FBeamPid>"))
struct BEAMABLECORE_API FOptionalArrayOfBeamPid : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<FBeamPid> Val;

	FOptionalArrayOfBeamPid();

	explicit FOptionalArrayOfBeamPid(TArray<FBeamPid> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};