#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/Enums/BeamOrderDirection.h"

#include "OptionalOrderDirection.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalOrderDirectionLibrary.MakeOptional", BeamOptionalType="EBeamOrderDirection"))
struct BEAMABLECORE_API FOptionalOrderDirection : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EBeamOrderDirection Val;

	FOptionalOrderDirection();

	explicit FOptionalOrderDirection(EBeamOrderDirection Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};