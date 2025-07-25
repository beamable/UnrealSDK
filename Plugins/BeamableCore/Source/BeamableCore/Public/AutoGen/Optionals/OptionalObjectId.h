#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/ObjectId.h"

#include "OptionalObjectId.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalObjectIdLibrary.MakeOptional", BeamOptionalType="UObjectId*"))
struct BEAMABLECORE_API FOptionalObjectId : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UObjectId* Val;

	FOptionalObjectId();

	explicit FOptionalObjectId(UObjectId* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};