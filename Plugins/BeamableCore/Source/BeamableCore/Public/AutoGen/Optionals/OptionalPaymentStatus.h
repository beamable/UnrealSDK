#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/Enums/BeamPaymentStatus.h"

#include "OptionalPaymentStatus.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalPaymentStatusLibrary.MakeOptional", BeamOptionalType="EBeamPaymentStatus"))
struct BEAMABLECORE_API FOptionalPaymentStatus : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EBeamPaymentStatus Val;

	FOptionalPaymentStatus();

	explicit FOptionalPaymentStatus(EBeamPaymentStatus Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};