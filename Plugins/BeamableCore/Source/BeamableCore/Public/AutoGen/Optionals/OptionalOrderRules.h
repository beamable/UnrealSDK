#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/OrderRules.h"

#include "OptionalOrderRules.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalOrderRulesLibrary.MakeOptional", BeamOptionalType="UOrderRules*"))
struct BEAMABLECORE_API FOptionalOrderRules : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UOrderRules* Val;

	FOptionalOrderRules();

	explicit FOptionalOrderRules(UOrderRules* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};