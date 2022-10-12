
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "AutoGen/OrderRules.h"

#include "OptionalOrderRules.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalOrderRulesLibrary.MakeOptionalOrderRules"))
struct FOptionalOrderRules : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	UOrderRules* Val;

	FOptionalOrderRules();

	explicit FOptionalOrderRules(UOrderRules* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};