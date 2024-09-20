#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/UpdateData.h"

#include "OptionalUpdateData.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalUpdateDataLibrary.MakeOptional", BeamOptionalType="UUpdateData*"))
struct BEAMABLECORE_API FOptionalUpdateData : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	UUpdateData* Val;

	FOptionalUpdateData();

	explicit FOptionalUpdateData(UUpdateData* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};