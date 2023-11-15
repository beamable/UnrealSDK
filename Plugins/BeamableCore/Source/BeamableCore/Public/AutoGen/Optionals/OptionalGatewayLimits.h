#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/GatewayLimits.h"

#include "OptionalGatewayLimits.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalGatewayLimitsLibrary.MakeOptional", BeamOptionalType="UGatewayLimits*"))
struct BEAMABLECORE_API FOptionalGatewayLimits : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UGatewayLimits* Val;

	FOptionalGatewayLimits();

	explicit FOptionalGatewayLimits(UGatewayLimits* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};