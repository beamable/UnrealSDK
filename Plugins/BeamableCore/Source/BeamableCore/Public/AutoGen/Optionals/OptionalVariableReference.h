#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/VariableReference.h"

#include "OptionalVariableReference.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalVariableReferenceLibrary.MakeOptional", BeamOptionalType="UVariableReference*"))
struct BEAMABLECORE_API FOptionalVariableReference : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UVariableReference* Val;

	FOptionalVariableReference();

	explicit FOptionalVariableReference(UVariableReference* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};