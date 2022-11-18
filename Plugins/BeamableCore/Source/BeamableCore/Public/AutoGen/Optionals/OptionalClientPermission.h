
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "AutoGen/ClientPermission.h"

#include "OptionalClientPermission.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalClientPermissionLibrary.MakeOptional", BeamOptionalType="UClientPermission*"))
struct BEAMABLECORE_API FOptionalClientPermission : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	UClientPermission* Val;

	FOptionalClientPermission();

	explicit FOptionalClientPermission(UClientPermission* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};