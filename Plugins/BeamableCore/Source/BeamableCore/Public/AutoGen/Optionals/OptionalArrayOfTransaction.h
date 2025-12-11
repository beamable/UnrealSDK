#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/Transaction.h"

#include "OptionalArrayOfTransaction.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfTransactionLibrary.MakeOptional", BeamOptionalType="TArray<UTransaction*>"))
struct BEAMABLECORE_API FOptionalArrayOfTransaction : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UTransaction*> Val;

	FOptionalArrayOfTransaction();

	explicit FOptionalArrayOfTransaction(TArray<UTransaction*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};