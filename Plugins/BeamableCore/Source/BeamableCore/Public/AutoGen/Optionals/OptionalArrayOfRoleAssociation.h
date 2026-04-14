#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/RoleAssociation.h"

#include "OptionalArrayOfRoleAssociation.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfRoleAssociationLibrary.MakeOptional", BeamOptionalType="TArray<URoleAssociation*>"))
struct BEAMABLECORE_API FOptionalArrayOfRoleAssociation : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<URoleAssociation*> Val;

	FOptionalArrayOfRoleAssociation();

	explicit FOptionalArrayOfRoleAssociation(TArray<URoleAssociation*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};