#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/PlayerSessionActorPaymentTotal.h"

#include "OptionalArrayOfPlayerSessionActorPaymentTotal.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfPlayerSessionActorPaymentTotalLibrary.MakeOptional", BeamOptionalType="TArray<UPlayerSessionActorPaymentTotal*>"))
struct BEAMABLECORE_API FOptionalArrayOfPlayerSessionActorPaymentTotal : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UPlayerSessionActorPaymentTotal*> Val;

	FOptionalArrayOfPlayerSessionActorPaymentTotal();

	explicit FOptionalArrayOfPlayerSessionActorPaymentTotal(TArray<UPlayerSessionActorPaymentTotal*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};