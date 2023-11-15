#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/RoleMapping.h"

#include "OptionalArrayOfRoleMapping.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfRoleMappingLibrary.MakeOptional", BeamOptionalType="TArray<URoleMapping*>"))
struct BEAMABLECORE_API FOptionalArrayOfRoleMapping : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<URoleMapping*> Val;

	FOptionalArrayOfRoleMapping();

	explicit FOptionalArrayOfRoleMapping(TArray<URoleMapping*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};