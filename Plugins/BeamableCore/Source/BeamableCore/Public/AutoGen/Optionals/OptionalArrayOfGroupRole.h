
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "AutoGen/GroupRole.h"

#include "OptionalArrayOfGroupRole.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalArrayOfGroupRoleLibrary.MakeOptional", BeamOptionalType="TArray<UGroupRole*>"))
struct BEAMABLECORE_API FOptionalArrayOfGroupRole : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<UGroupRole*> Val;

	FOptionalArrayOfGroupRole();

	explicit FOptionalArrayOfGroupRole(TArray<UGroupRole*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};