#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/Enums/BeamTransactionState.h"

#include "OptionalTransactionState.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalTransactionStateLibrary.MakeOptional", BeamOptionalType="EBeamTransactionState"))
struct BEAMABLECORE_API FOptionalTransactionState : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EBeamTransactionState Val;

	FOptionalTransactionState();

	explicit FOptionalTransactionState(EBeamTransactionState Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};