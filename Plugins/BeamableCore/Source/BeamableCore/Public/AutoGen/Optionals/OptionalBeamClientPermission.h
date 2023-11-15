#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamBackend/ReplacementTypes/BeamClientPermission.h"

#include "OptionalBeamClientPermission.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalBeamClientPermissionLibrary.MakeOptional", BeamOptionalType="FBeamClientPermission"))
struct BEAMABLECORE_API FOptionalBeamClientPermission : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FBeamClientPermission Val;

	FOptionalBeamClientPermission();

	explicit FOptionalBeamClientPermission(FBeamClientPermission Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};