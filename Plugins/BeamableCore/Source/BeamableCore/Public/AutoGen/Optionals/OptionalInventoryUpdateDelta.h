#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/InventoryUpdateDelta.h"

#include "OptionalInventoryUpdateDelta.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalInventoryUpdateDeltaLibrary.MakeOptional", BeamOptionalType="UInventoryUpdateDelta*"))
struct BEAMABLECORE_API FOptionalInventoryUpdateDelta : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UInventoryUpdateDelta* Val;

	FOptionalInventoryUpdateDelta();

	explicit FOptionalInventoryUpdateDelta(UInventoryUpdateDelta* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};