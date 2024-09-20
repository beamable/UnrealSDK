#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/OptionalJsonNodeWrapper.h"

#include "OptionalOptionalJsonNodeWrapper.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalOptionalJsonNodeWrapperLibrary.MakeOptional", BeamOptionalType="UOptionalJsonNodeWrapper*"))
struct BEAMABLECORE_API FOptionalOptionalJsonNodeWrapper : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	UOptionalJsonNodeWrapper* Val;

	FOptionalOptionalJsonNodeWrapper();

	explicit FOptionalOptionalJsonNodeWrapper(UOptionalJsonNodeWrapper* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};