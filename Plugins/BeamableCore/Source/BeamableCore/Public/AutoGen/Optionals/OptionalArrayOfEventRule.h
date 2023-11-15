#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/EventRule.h"

#include "OptionalArrayOfEventRule.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfEventRuleLibrary.MakeOptional", BeamOptionalType="TArray<UEventRule*>"))
struct BEAMABLECORE_API FOptionalArrayOfEventRule : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UEventRule*> Val;

	FOptionalArrayOfEventRule();

	explicit FOptionalArrayOfEventRule(TArray<UEventRule*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};