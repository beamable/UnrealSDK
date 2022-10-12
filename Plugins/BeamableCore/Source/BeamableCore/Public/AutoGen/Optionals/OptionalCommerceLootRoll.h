
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "AutoGen/CommerceLootRoll.h"

#include "OptionalCommerceLootRoll.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalCommerceLootRollLibrary.MakeOptionalCommerceLootRoll"))
struct FOptionalCommerceLootRoll : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	UCommerceLootRoll* Val;

	FOptionalCommerceLootRoll();

	explicit FOptionalCommerceLootRoll(UCommerceLootRoll* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};