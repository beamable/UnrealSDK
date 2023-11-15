#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/GamerTagAssociation.h"

#include "OptionalGamerTagAssociation.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalGamerTagAssociationLibrary.MakeOptional", BeamOptionalType="UGamerTagAssociation*"))
struct BEAMABLECORE_API FOptionalGamerTagAssociation : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UGamerTagAssociation* Val;

	FOptionalGamerTagAssociation();

	explicit FOptionalGamerTagAssociation(UGamerTagAssociation* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};